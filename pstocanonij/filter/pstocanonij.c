/*
 *  CUPS add-on module for Canon Inkjet Printer.
 *  Copyright CANON INC. 2001-2012
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 */
#include <cups/cups.h>
#include <cups/ppd.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <errno.h>


#include "paramlist.h"
#include "buflist.h"
#include "canonopt.h"

//#define DEBUG_SLEEP
//#define DEBUG_PS
//#define DEBUG_IN_PS


#if HAVE_CONFIG_H
#include <config.h>
#endif

#define FILTER_PATH    PROG_PATH
//#define FILTER_PATH    "/usr/local/bin"
#define FILTER_BIN     "cif"

#define GS_PATH        "/usr/bin"
#define GS_BIN         "gs"
#define SHELL_PATH     "/bin"
#define SHELL_NAME     "sh"


#define	TABLE_BUF_SIZE	1024
#define	LINE_BUF_SIZE	1024
#define	DATA_BUF_SIZE	(1024 * 256)
#define	PARAM_BUF_SIZE	256


#define IS_BLANK(c)		(c == ' '  || c == '\t')
#define IS_RETURN(c)	(c == '\r' || c == '\n')
#define IS_NUMBER(c)	(c >= '0' && c <= '9')

#define ACRO_UTIL "%%BeginResource: procset Adobe_CoolType_Utility_MAKEOCF"
#define ACRO_UTIL_LEN 55

//For InkJet filter
#define PAGE_DEV_BEGIN	"<<"
#define PAGE_DEV_END	">>setpagedevice"

#define	LONG_EDGE	"--stapleside longside"
#define	SHORT_EDGE	"--stapleside shortside"

/* Ver.3.00 */
#define	P_TOPLEFT	0
#define	P_CENTER	1

int g_filter_pid = -1;
int g_signal_received = 0;

#ifdef	DEBUG_IN_PS
int g_in_log_fd = -1;
#endif


static
int is_size_X(char *str)
{
	int is_size = 1;

	while( *str && is_size )
	{
		if( *str == '.' ) break;	/* Ver.2.90 */

		switch( is_size )
		{
		case 1:
			if( IS_NUMBER(*str) )
				is_size = 2;
			else
				is_size = 0;
			break;
		case 2:
			if( *str == 'X' )
				is_size = 3;
			else if( !IS_NUMBER(*str) )
				is_size = 0;
			break;
		case 3:
		case 4:
			if( IS_NUMBER(*str) )
				is_size = 4;
			else
				is_size = 0;
			break;

		}
		str++;
	}

	return (is_size == 4)? 1 : 0;
}

void to_lower_except_size_X(char *str)
{
	if( !is_size_X(str) )
	{
		while( *str )
		{
			if( *str >= 'A' && *str <= 'Z' )
				*str = *str - 'A' + 'a';
			str++;
		}
	}
}

static 
int is_acro_util(char *p_data_buf, int read_bytes)
{
	if( strncmp(p_data_buf, ACRO_UTIL, ACRO_UTIL_LEN) == 0 )
		return 1;
	else
		return 0;
}

static 
int is_end_resource(char *p_data_buf, int read_bytes)
{
	if( strncmp(p_data_buf, "%%EndResource", 13) == 0 )
		return 1;
	else
		return 0;
}

static
int read_line(int fd, char *p_buf, int bytes)
{
	static char read_buf[DATA_BUF_SIZE];
	static int buf_bytes = 0;
	static int buf_pos = 0;
	int read_bytes = 0;

	while( bytes > 0 )
	{
		if( buf_bytes == 0 && fd != -1 )
		{
			buf_bytes = read(fd, read_buf, DATA_BUF_SIZE);

			if( buf_bytes > 0 )
			{
#ifdef	DEBUG_IN_PS
				if( g_in_log_fd > 0 )
					write(g_in_log_fd, read_buf, buf_bytes);
#endif
				buf_pos = 0;
			}
		}

		if( buf_bytes > 0 )
		{
			*p_buf = read_buf[buf_pos++];
			bytes--;
			buf_bytes--;
			read_bytes++;

			if( IS_RETURN(*p_buf) )
				break;

			p_buf++;
		}
		else if( buf_bytes < 0 )
		{
			if( errno == EINTR )
				continue;
		}
		else
			break;
	}

	return read_bytes; 
}

static
ParamList *get_ps_params(int ifd, BufList **ps_data)
{
	char read_buf[DATA_BUF_SIZE];
	ParamList *p_list = NULL;
	int begin_page = 0;
	int read_bytes;
	int acro_util = 0;	
	BufList *bl = NULL;
	BufList *prev_bl = NULL;
	int NumCopies = 0;		// Ver.3.50
	int FlagCopies = 0;		// Ver.3.50
	char *StrCopies = NULL;	// Ver.3.50
	int FlagLanguageLevel = 0;	// Ver.3.50
	/* ver.3.80 Landscape/Portrait */
	int endpage_count = 0;
	int line_count = 0;
	int endpage_flg = 0;
	int rotate_flg = 0;
	int rotate_info = 0;
	char rotate_buf[16];
	/* ver.3.80 Landscape/Portrait */

	memset(rotate_buf, 0, 16);

	while( (read_bytes = read_line(ifd, read_buf, DATA_BUF_SIZE - 1)) > 0 )
	{
		int dev_len = strlen(PAGE_DEV_BEGIN);
		int end_len = strlen(PAGE_DEV_END);

		// For Acrobat Reader 
		{
			if( is_acro_util(read_buf, read_bytes) ){
				acro_util = 1;	
			}
			else if( acro_util && is_end_resource(read_buf, read_bytes) ){
				acro_util = 0;	
			}

			if( acro_util ){
				int line_bytes=0;
				while( line_bytes+29 < read_bytes ){
					if(!strncmp(&read_buf[line_bytes], 
						" ct_BadResourceImplementation?", 30)){
						strcpy(&read_buf[line_bytes], " false");
						line_bytes+=6;
						strcpy(&read_buf[line_bytes], 
							&read_buf[line_bytes+24]);
						read_bytes-=24;
					}
					else{
						line_bytes++;
					}
				}
			}
		}

		/* ver.3.80 Landscape/Portrait */
		if( read_bytes > 6 ){
			if( (strncmp(&read_buf[read_bytes-5], "] cm", 4) == 0) || (strncmp(&read_buf[read_bytes-5], "] Tm", 4) == 0) ){
			//if( strncmp(&read_buf[read_bytes-5], "] cm", 4) == 0 ){
				char *tok;
				char dimx[4][32];
				int k;

			 	fprintf( stderr, "DEBUG: ###find cm/Tm[ = %d: %s, \n" ,line_count, read_buf );

				tok = strtok( &read_buf[1], " " );
				strncpy(dimx[0], tok, 32);
				dimx[0][31] = '\0';
				fprintf( stderr, "DEBUG: dimx[0] = %s\n" ,dimx[0] );
				for( k=1; k<4; k++ ){
					tok = strtok( NULL, " " );
					strncpy(dimx[k], tok, 32);
					dimx[k][31] = '\0';
					fprintf( stderr, "DEBUG: dimx[%d] = %s\n", k, dimx[k] );
				}
				
				if( (strncmp( dimx[1], dimx[2], 32) == 0) && (strncmp( dimx[1], "0", 32) == 0) ){
					if( strncmp( dimx[0], "-", 1) == 0 ){
						rotate_info = 2;  /* Rotate:180 */
					}
					else{
						rotate_info = 0;  /* Rotate:  0 */
					}
				}
				else if( (strncmp( dimx[0], dimx[3], 32) == 0) && (strncmp( dimx[0], "0", 32) == 0) ){
					if( strncmp( dimx[1], "-", 1) == 0 ){
						rotate_info = 1;  /* Rotate:270 */
					}
					else{
						rotate_info = 3;  /* Rotate: 90 */
					}
				}
				else{
					 rotate_info = 0;
				}
			 	rotate_flg = 1;
			 }
		}
		line_count = line_count + 1;
		/* ver.3.80 Landscape/Portrait */

		/* ver.3.50 File Transfer */
		if( (strncmp(read_buf, "%%LanguageLevel: 2", 18) == 0) || (strncmp(read_buf, "%%LanguageLevel: 3", 18) == 0) )
		{
			FlagLanguageLevel = 1;
		}
		if( strncmp(read_buf, "%RBIBeginNonPPDFeature:", 23) == 0 )
		{	
			FlagCopies = 1;
		}
		else if( (strncmp(read_buf, "/#copies", 8) == 0) && (FlagLanguageLevel == 1) )
		{
			StrCopies = strchr( read_buf, ' ' );
			if( StrCopies != NULL )
			{
				NumCopies = atoi( StrCopies + 1 );
				sprintf( StrCopies, "%d", NumCopies );
				fprintf( stderr, "DEBUG: Copies = %s(PostScriptLevel3)¥n", StrCopies );
				param_list_add_multi(&p_list, "CNCopies", StrCopies, strlen(StrCopies) + 1, 1);
			}
			FlagCopies = 0;
			strncpy( read_buf, "%%%%", read_bytes );
		}
		if( (FlagCopies == 1) && (FlagLanguageLevel == 1) )
		{
			if( strncmp(read_buf, "%RBIEndNonPPDFeature", 20) == 0 )
			{
				FlagCopies = 0;
			}
			strncpy( read_buf, "%%%%", read_bytes );
		}
		/* ver.3.50 end */

		// Retain the PS data in the buffer list.
		bl = buflist_new((unsigned char *)read_buf, read_bytes);

		if( *ps_data == NULL )
			*ps_data = bl;
		else
			buflist_add_tail(prev_bl, bl);

		prev_bl = bl;

		if( read_bytes > 0 )
		{
			if( read_buf[read_bytes - 1] == '\n' )
				read_buf[read_bytes - 1] = '\0';
			else
				read_buf[read_bytes] = '\0';
		}
		else
		{
			read_buf[0] = '\0';
		}

		// Parse the printing option per line.
		if( strncmp(read_buf, "%%BeginFeature:", 15) == 0 )
		{
			char key_buf[MAX_KEY_LEN + 1];
			char value_buf[MAX_VALUE_LEN + 1];
			int key_len = 0;
			int value_len = 0;
			char *p_code;

			memset(key_buf, 0, MAX_KEY_LEN + 1);
			memset(value_buf, 0, MAX_VALUE_LEN + 1);
			p_code = read_buf + 15;

			while( *p_code != '\0' )
			{
				if( *p_code++ == '*' )
					break;
			}
			while( *p_code != '\0' )
			{
				if( IS_BLANK(*p_code)
				 || key_len >= MAX_KEY_LEN )
					break;
				key_buf[key_len++] = *p_code++;
			}
			while( *p_code != '\0' )
			{
				if( !IS_BLANK(*p_code)  )
					break;
				//*p_code++;
				p_code++;
			}
			while( *p_code != '\0' )
			{
				if( IS_BLANK(*p_code)
				 || value_len >= MAX_VALUE_LEN )
					break;
				value_buf[value_len++] = *p_code++;
			}
			if( key_len > 0 && value_len > 0 )
			{
				key_buf[key_len] = '\0';
				value_buf[value_len] = '\0';

				param_list_add_multi(&p_list, key_buf, value_buf, value_len + 1, 1);
			}
		}

		/* Ver.3.50 Start */
		else if( (strncmp(read_buf, "%RBINumCopies:", 14) == 0) && (FlagLanguageLevel == 1) )
		{
			StrCopies = strchr( read_buf, ' ' );
			if( StrCopies != NULL )
			{
				NumCopies = atoi( StrCopies + 1 );
				sprintf( StrCopies, "%d", NumCopies );
				fprintf( stderr, "DEBUG: Copies = %s(PostScriptLevel2)¥n", StrCopies );
				param_list_add_multi(&p_list, "CNCopies", StrCopies, strlen(StrCopies) + 1, 1);
			}
		}
		/* Ver.3.50 end */

		else if( !begin_page && strncmp(read_buf, "%%Page:", 7) == 0 )
		{
			begin_page = 1;
		}
		else if( begin_page )
		{
			/* ver.3.80 Landscape/Portrait */
			/* EndPageSetup etc from 100 line */
			if( (endpage_flg == 1) && ( (rotate_flg == 1) || ((endpage_count + 100) < line_count)) ) {
				fprintf( stderr, "DEBUG: ****$$$ endpage_count,line_count = %d, %d\n",endpage_count, line_count );
				break;
			}
			/* ver.3.80 Landscape/Portrait */

			if( strncmp(read_buf, "%%EndPageSetup", 14) == 0 ){
				if( endpage_flg == 0 ){
					endpage_count = line_count;
				}
				endpage_flg = 1;
				/* break; */
			}
			else if( strncmp(read_buf, "gsave", 5) == 0 ){
				if( endpage_flg == 0 ){
					endpage_count = line_count;
				}
				endpage_flg = 1;
				/* break; */
			}

			else if( read_buf[0] >= '0' && read_buf[0] <= '9' ){
				if( endpage_flg == 0 ){
					endpage_count = line_count;
				}
				endpage_flg = 1;
				/* break; */
			}

			/* ver.3.80 Landscape/Portrait */
			/* if( strncmp(read_buf, "%%EndPageSetup", 14) == 0 ) */
			/* 	break; */
			/* else if( strncmp(read_buf, "gsave", 5) == 0 ) */
			/* 	break; */
			/* else if( read_buf[0] >= '0' && read_buf[0] <= '9' ) */
			/* 	break; */
		}
		/* For InkJet <</xxx(...)>>setpagedevice. */
		else if(strncmp(read_buf + (read_bytes - 1 - end_len), PAGE_DEV_END, end_len) == 0)
		{
			char key_buf[MAX_KEY_LEN + 1];
			char value_buf[MAX_VALUE_LEN + 1];
			char *p_code;
			int pos = 0;

			memset(key_buf, 0, MAX_KEY_LEN + 1);
			memset(value_buf, 0, MAX_VALUE_LEN + 1);
			p_code = read_buf + dev_len;

			while( !IS_RETURN(p_code[pos]) )
			{
				int key_pos = 0;
				int val_pos = 0;

				while( p_code[pos] != '/'
				        && !IS_RETURN(p_code[pos]) ) pos++;

				if( p_code[pos] == '/' ) pos++;
				else continue;

				while( isalnum(p_code[pos])
						&& key_pos < 255 )
					key_buf[key_pos++] = p_code[pos++];

				key_buf[key_pos++] = 0;

				if( p_code[pos] == '(' )
				{
					pos++;

					while( p_code[pos] != ')'
						&& !IS_BLANK(p_code[pos])
						&& !IS_RETURN(p_code[pos])
						&& val_pos < 255 )
						value_buf[val_pos++] = p_code[pos++];

					value_buf[val_pos++] = 0;

					if( p_code[pos] == ')' ) pos++;
					else continue;

					if( !strcmp(key_buf, "CNPageSizeName") )
						strncpy(key_buf, "PageSize", MAX_KEY_LEN);
				}
				else continue;

				param_list_add_multi(&p_list, key_buf, value_buf, val_pos+1, 1);
			}
		}
	}
	
	/* ver.3.80 Landscape/Portrait */
	fprintf( stderr, "DEBUG: ****$$$ rotate_info = %d\n",rotate_info );
	snprintf(rotate_buf, 16, "%d", rotate_info);
	param_list_add_multi(&p_list, "CNRotate", rotate_buf, strlen(rotate_buf) + 1, 1);
	/* ver.3.80 Landscape/Portrait */

	while( (read_bytes = read_line(-1, read_buf, DATA_BUF_SIZE - 1)) > 0 )
	{
		BufList *bl = buflist_new((unsigned char *)read_buf, read_bytes);

		if( *ps_data == NULL )
			*ps_data = bl;
		else
			buflist_add_tail(prev_bl, bl);

		prev_bl = bl;

		if( read_bytes > 0 )
		{
			if( read_buf[read_bytes - 1] == '\n' )
				read_buf[read_bytes - 1] = '\0';
			else
				read_buf[read_bytes] = '\0';
		}
		else
		{
			read_buf[0] = '\0';
		}
	}
	return p_list;
}

static
int is_borderless(char* size_name)
{
	int len = strlen(size_name);

	if( !strcmp(&size_name[len - 3], ".bl") )
	{
		size_name[len - 3] = 0;
		return 1;
	}
	else
		return 0;
}

static
void mark_ps_param_options(ppd_file_t *p_ppd, ParamList *p_param)
{
	int num = param_list_num(p_param);

	if( num > 0 )
	{
		cups_option_t *options
			= (cups_option_t*)malloc(num * sizeof(cups_option_t));
		if( options )
		{
			int i;
			for( i = 0 ; i < num ; i++ )
			{
				options[i].name = p_param->key;
				options[i].value = p_param->value;
				p_param = p_param->next;
			}
			for( i = num - 1 ; i >= 0 ; i-- )
			{
				cupsMarkOptions(p_ppd, 1, &options[i]);

#ifdef	DEBUG_IN_PS
				ppd_option_t	*o;
				short	j;
	
				fprintf(stderr,"DEBUG: ### mark_ps_param_options(%d) : %s=%s ###\n" , i,options[i].name,options[i].value);

				fprintf(stderr,"DEBUG: ** p_ppd->size after cupsMarkOptions num=%d **\n" , p_ppd->num_sizes);
				for( j = 0 ; j < p_ppd->num_sizes; j++ ){
					fprintf(stderr,"DEBUG: ** p_ppd->size after cupsMarkOptions: %s marked=%d **\n" , p_ppd->sizes[j].name, p_ppd->sizes[j].marked);
				}
				o = ppdFindOption( p_ppd , "PageSize" );
				if( o != NULL){
					for( j = 0 ; j < o->num_choices; j++ ){
						fprintf(stderr,"DEBUG: ** PageSize after cupsMarkOptions: %s marked=%d **\n" , o->choices[j].text, o->choices[j].marked);
					}
				}else{
					fprintf(stderr,"DEBUG: ** PageSize after cupsMarkOptions :o = ppdFindOption = NULL **\n");
				}

				o = ppdFindOption( p_ppd , "PageRegion" );
				if( o != NULL){
					for( j = 0 ; j < o->num_choices; j++ ){
						fprintf(stderr,"DEBUG: ** PageRegion after cupsMarkOptions: %s marked=%d **\n" , o->choices[j].text, o->choices[j].marked);
					}
				}else{
					fprintf(stderr,"DEBUG: ** PageRegion after cupsMarkOptions :o = ppdFindOption = NULL **\n");
				}
#endif
			}

			free(options);
		}
	}
}

static
void get_min_max_width_length(PpdToOptKey *p_table, cups_option_t *p_opt, int num_opt, long *p_minw_mm, long *p_maxw_mm, long *p_minl_mm, long *p_maxl_mm)
{
	*p_minw_mm = -1;
	*p_maxw_mm = -1;
	*p_minl_mm = -1;
	*p_maxl_mm = -1;

	while( num_opt-- > 0 )
	{
		if( !strcmp(p_opt->name, "CNMinWidth") )	/* Only if lpr is excuted by "cngpij", CNMinWidth etc. has value. */
			*p_minw_mm = atoi(p_opt->value);
		else if( !strcmp(p_opt->name, "CNMaxWidth") )
			*p_maxw_mm = atoi(p_opt->value);
		else if( !strcmp(p_opt->name, "CNMinLength") )
			*p_minl_mm = atoi(p_opt->value);
		else if( !strcmp(p_opt->name, "CNMaxLength") )
			*p_maxl_mm = atoi(p_opt->value);

		p_opt++;
	}
}

static
char *parse_product_name(char *ppd_product, char *product, int len)
{
	char *p_product = product;
	char *p_cc;
	int count = 0;

	memset(product, 0, len);
	p_cc = ppd_product;

	while( *p_cc == '(' )
		p_cc++;

	while( *p_cc != ')' && *p_cc != '\0' && count < len - 1 )
	{
		*p_product++ = *p_cc++;
		count++;
	}
	*p_product = '\0';

	return product;
}

char** make_filter_param_list(char *model, int reso,
		ParamList *pl, ParamList **cmd_list)
{
	char* cmd_name = NULL;
	char* cmd_path = NULL;
	ParamList *curs;
	int cmd_num;
	char **cmd_buf;
	int cmd_buf_index;
	char reso_buf[MAX_VALUE_LEN + 1];

	short	borderless_on = 0;
	short	ext_on = 0;
	char	ext_value[256];
	
	memset( ext_value , 0x00 , 256 );

	// Make command path.
	cmd_name = (char*)malloc(strlen(FILTER_BIN) + strlen(model) + 1);
	strcpy(cmd_name, FILTER_BIN);
	strcat(cmd_name, model);

	cmd_path =  (char*)malloc(strlen(FILTER_PATH) + strlen(cmd_name) +2 );	/* Ver.2.90(+2 "/","\0") */
	strcpy(cmd_path, FILTER_PATH);
	strcat(cmd_path, "/");
	strcat(cmd_path, cmd_name);

	for( curs = pl ; curs != NULL ; curs = curs->next )
	{
		char value_buf[MAX_VALUE_LEN + 1];

		fprintf(stderr,"DEBUG: make_filter_param_list: %s\n",curs->key);

		if( !strcmp( curs->key , "--borderless" ) ) borderless_on = 1;

		/* "--extension" is not added here yet. */
		if( !strcmp( curs->key , "--extension" ) )
		{
			ext_on = 1;
			memcpy(ext_value, curs->value, curs->value_size);
			ext_value[curs->value_size] = 0;
			continue;
		}

		/* "--percent" is ignored. (Ver.3.00) */
		if( !strcmp( curs->key , "--percent" ) )
		{
			continue;
		}

		if( strlen(curs->key) + 1 > MAX_KEY_LEN )
			continue;
		if( curs->value_size + 1 > MAX_VALUE_LEN )
			continue;

		memcpy(value_buf, curs->value, curs->value_size);
		value_buf[curs->value_size] = 0;

		param_list_add(cmd_list, curs->key, value_buf, curs->value_size + 1);
	}

	/* If Borderless Printing is OFF, "--extension" is ignored. */
	if( ext_on && borderless_on ){
		param_list_add(cmd_list, "--extension", ext_value, strlen(ext_value) + 1);
	}

	// Make resolution string.
	snprintf(reso_buf, 255, "%d", reso);
	param_list_add(cmd_list, "--imageres", reso_buf, strlen(reso_buf) + 1);

	cmd_num = param_list_num(*cmd_list);
	cmd_buf = (char**)malloc((cmd_num * 2 + 3) * sizeof(char*));

	cmd_buf[0] = cmd_path;
	cmd_buf[1] = cmd_name;
	cmd_buf_index = 2;

	for( curs = *cmd_list ; curs != NULL ; curs = curs->next )
	{
		if( strcmp(curs->value, "false") )
		{
			cmd_buf[cmd_buf_index++] = curs->key;
			if( strcmp(curs->value, "true") )
			{
				cmd_buf[cmd_buf_index++] = curs->value;
			}
		}
	}
	cmd_buf[cmd_buf_index] = NULL;

	return cmd_buf;
}

char* make_filter_param_line(char *model, int reso, ParamList *pl)
{
	ParamList *cmd_list = NULL;
	char *cmd_buf = NULL;
	char **cmd_param;

	cmd_param = make_filter_param_list(model, reso, pl, &cmd_list);

	if( cmd_param )
	{
		int buf_len = 0;
		int i;

		for( i = 0 ; cmd_param[i] != NULL ; i++ )
		{
			if( i == 1 )
				continue;
			buf_len += strlen(cmd_param[i]) + 2;
		}

		cmd_buf = malloc(buf_len);

		if( cmd_buf != NULL )
		{
			*cmd_buf = 0;

			for( i = 0 ; cmd_param[i] != NULL ; i++ )
			{
				if( i == 1 )
					continue;
				strcat(cmd_buf, cmd_param[i]);
				strcat(cmd_buf, " ");
			}
			cmd_buf[buf_len - 2] = 0;
		}
		free(cmd_param);
	}

	if( cmd_list != NULL )
		param_list_free(cmd_list);

	return cmd_buf;
}


/* Ver.2.70 */
static short parse_custom_size(char *param , char *width , char *height , char *unit , short param_len )
{
	short	i,j;
	char	lpr_custom_width[256];
	char	lpr_custom_height[256];
	char	lpr_custom_unit[256];
	short	result = -1;

	memset(lpr_custom_width, 0x00, 256);
	memset(lpr_custom_height, 0x00, 256);
	memset(lpr_custom_unit, 0x00, 256);

	/* Width */
	for( i = 0, j = 0 ; i < param_len  ; i++, j++){
		if( param[i] == 'x' ) break;
		lpr_custom_width[j] = param[i];
	}
	lpr_custom_width[j] = '\0';
	if( strlen( lpr_custom_width ) == 0 ) goto  onErr;

	/* Height */
	for( i = strlen(lpr_custom_width) + 1, j = 0 ; i < param_len ; i++, j++ ){
		if( ( param[i] < '0' || param[i] > '9') && param[i] != '.' ) break;
		lpr_custom_height[j] = param[i];
	}
	lpr_custom_height[j] = '\0';
	if( strlen( lpr_custom_height ) == 0 ) goto  onErr;

	/* Unit */
	for( j = 0 ;  i < param_len ; i++ , j++ ){
		if( param[i] == '\0' ) break;
		lpr_custom_unit[j] = param[i];
	}
	lpr_custom_unit[j] = '\0';
		

	strncpy( width , lpr_custom_width , 256 );
	width[256-1] = '\0';

	strncpy( height , lpr_custom_height , 256 );
	height[256-1] = '\0';

	strncpy( unit , lpr_custom_unit , 256 );
	unit[256-1] = '\0';

	result = 0;	/* no error */

onErr:
	return result;
}


static
char* make_cmd_param(cups_option_t *p_cups_opt, int num_opt,
	ParamList *p_param, char *p_product, int len)
{
#ifdef DEBUG_PPD
	char *p_ppd_name = "debug.ppd";
#else
	char *p_ppd_name = getenv("PPD");
#endif
	ppd_file_t *p_ppd;
	char *cmd_buf = NULL;
	ppd_choice_t *p_choice;
	ppd_size_t *p_size;
	ppd_size_t *p_size_default;
	int reso;
	char gs_exec_buf[256];
	char gs_cmd_buf[1024];
	char *flt_cmd_buf = NULL;

	/* Ver.3.20 */
	char	*device_uri = getenv("DEVICE_URI");
	char	*canon_usb_backend_str = "cnijusb:";
	char	*canon_net_backend_str = "cnijnet:";
	short	canon_backend_flag = 0;
	short	rotate_flag = 0;


//For InkJet
	long minw_mm, maxw_mm;
	long minl_mm, maxl_mm;
	PpdToOptKey *p_opt_key_table = alloc_opt_key_table(p_ppd_name);
	PpdToOptKey *p_table = p_opt_key_table;
	ParamList *p_list = NULL;

	/* Ver.2.70 */
	char lpr_custom_size[256];
	char lpr_custom_width[256];
	char lpr_custom_height[256];
	char lpr_custom_unit[256];
	short ret = -1;

	/* Ver.2.90 */
	short	borderless_exist = 0;
	/* Ver.3.00 */
	short	position_exist = -1;

	memset(lpr_custom_size, 0x00, 256);
	memset(lpr_custom_width, 0x00, 256);
	memset(lpr_custom_height, 0x00, 256);
	memset(lpr_custom_unit, 0x00, 256);

	/* Ver.3.20 */
	fprintf(stderr,"DEBUG: device_uri=(%s)\n",device_uri);
	if( !strncmp( device_uri , canon_usb_backend_str , strlen( canon_usb_backend_str ) ) ) canon_backend_flag = 1;
	else if( !strncmp( device_uri , canon_net_backend_str , strlen( canon_net_backend_str ) ) ) canon_backend_flag = 1;

	if( (p_ppd = ppdOpenFile(p_ppd_name)) == NULL )
		return NULL;

	/* Ver.3.20 */
	if( p_ppd->model_number < 356 ) canon_backend_flag = 0;
	/* fprintf(stderr,"DEBUG: p_ppd->model_number=(%d)\n",p_ppd->model_number); */

	/* Ver.3.80 */
	if( p_ppd->model_number < 401 ) rotate_flag = 0;
	else                            rotate_flag = 1;

	if( p_opt_key_table == NULL)
		return NULL;

	{
		short i = 0;
		cups_option_t	*lpr_opt;			/* Current option */
		
		for ( i = num_opt, lpr_opt = p_cups_opt; i > 0; i --, lpr_opt ++){
			if( !strcmp(lpr_opt->name, "PageSize") && !strncmp(lpr_opt->value, "Custom" , 6) )
			{
				fprintf(stderr,"DEBUG: name=%s value=%s\n",lpr_opt->name,lpr_opt->value);
	
				/* lpr_custom_size : (ex) "100x150mm" */
				strncpy( lpr_custom_size , (lpr_opt->value)+7 , 256 );
				lpr_custom_size[256 -1] = '\0';
				fprintf(stderr,"DEBUG: lpr_custom_size=%s\n",lpr_custom_size);
				
				ret = parse_custom_size( lpr_custom_size , lpr_custom_width , lpr_custom_height , lpr_custom_unit , strlen(lpr_custom_size) );
	
				fprintf(stderr,"DEBUG: lpr_custom_width=%s lpr_custom_height=%s lpr_custom_unit=%s\n",
						lpr_custom_width,lpr_custom_height,lpr_custom_unit);
			}
		}
	}


	ppdMarkDefaults(p_ppd);

	p_size_default = ppdPageSize(p_ppd, NULL);

	/* (1)Mark options from PostScript headers. */
	mark_ps_param_options(p_ppd, p_param);	//PS header might include CNExtension...


	/* Ver.2.90: IF - Current p_size is not the default size, */
	/*              - p_cups_opt includes "media" option, */
	/*              - p_cups_opt DOES NOT includes "PageSize" option */
	/*       --> then, add "PageSize" option with the value of current size to p_cups_opt. */
	
	p_size = ppdPageSize(p_ppd, NULL);	/* Get "ppd_size_t" of current size by CUPS system (unit of width and height is "point") */
	fprintf(stderr,"DEBUG: #  p_size->name=%s , p_size_default->name = %s #\n" , p_size->name, p_size_default->name );

	if( strcasecmp( p_size->name , p_size_default->name) )/* If p_size is not the default size */
	{
		short	media_exist = 0;
		short	pagesize_exist = 0;
		short	i;
		cups_option_t	*optptr;		/* Current option */
	
		for (i = num_opt, optptr = p_cups_opt; i > 0; i --, optptr ++)
		{
			if (!strcasecmp(optptr->name, "media")) media_exist = 1;
			if (!strcasecmp(optptr->name, "PageSize")) pagesize_exist = 1;
		}
		fprintf(stderr,"DEBUG: # media_exist=%d , pagesize_exist = %d #\n" , media_exist, pagesize_exist );
		
		if( media_exist && (!pagesize_exist) )
		{
	        num_opt = cupsAddOption( "PageSize" , p_size->name , num_opt, &p_cups_opt );
		}
	}
	

	/* (2)Mark options from lpr parameters(p_cups_opt). */
	cupsMarkOptions(p_ppd, num_opt, p_cups_opt);
	fprintf(stderr,"DEBUG: ### num_opt(lpr optins) = %d ###\n" , num_opt );

	// Obtain page size setting.
//	p_choice = ppdFindMarkedChoice(p_ppd, "PageSize");
//	p_size = ppdPageSize(p_ppd, p_choice->choice);	/* Get "ppd_size_t" by CUPS system (unit of width and height is "point")
	/* Ver.2.90: Use "NULL" to get size of current setting */
	p_size = ppdPageSize(p_ppd, NULL);	/* Get "ppd_size_t" by CUPS system (unit of width and height is "point") */


	fprintf(stderr,"DEBUG: \n# ppdPageSize width=%f height=%f ###\n\n" , p_size->width,p_size->length );


	// Obtain resolution setting.
	p_choice = ppdFindMarkedChoice(p_ppd, "Resolution");
	reso = atoi(p_choice->choice);

	//Obtain product name.
	parse_product_name(p_ppd->product, p_product, len);

	get_min_max_width_length(p_opt_key_table, p_cups_opt, num_opt,
		&minw_mm, &maxw_mm, &minl_mm, &maxl_mm);

	/* Make "gs command" */
	memset(gs_exec_buf, 0, 256);
	strncpy(gs_exec_buf, GS_PATH, 255);
	strncat(gs_exec_buf, "/", 255 - strlen(gs_exec_buf));
	strncat(gs_exec_buf, GS_BIN, 255 - strlen(gs_exec_buf));
	snprintf(gs_cmd_buf, 1023,
	"%s -sstdout=%%stderr -r%d -g%dx%d -q -dNOPROMPT -dSAFER -sDEVICE=ppmraw -sOutputFile=%%stdout -| ",
			gs_exec_buf, reso, (int)(p_size->width * (float)reso / 72.0),
			(int)(p_size->length * (float)reso / 72.0));


	/*********** For InkJet filter Command ************************/

	/* (3)Make cif options from p_ppd and p_table , then store them in  p_list. */
	// p_table: Contain all options described in PPD file. (include vender specific options)
	// p_ppd  : Contain generic options included in ppd_file_t structure. (not include vender specific options)
	while( p_table->ppd_key != NULL )
	{
		p_choice = ppdFindMarkedChoice(p_ppd, p_table->ppd_key);
		/* Vender specific options that are not shown application UI are not found in p_ppd.(So, they are not treated here.) */
		if( p_choice ) fprintf(stderr,"DEBUG: (3)Make cif options : p_choice found in p_ppd (p_choice:%s /  %s)\n",p_choice->text,p_choice->choice);
		else  fprintf(stderr,"DEBUG: (3)Make cif options : %s is not found in p_ppd\n",p_table->ppd_key);
		
		if( p_choice != NULL )
		{
			char choice[256];

			memset(choice, 0, 256);
			strncpy(choice, p_choice->choice, 255);

			/* Page Size=Custom */
			if( !strcmp(p_table->ppd_key, "PageSize")
			 && !strcmp(choice, "Custom") )
			{
				char pw[256];
				char pl[256];
				long pw_mm, pl_mm;
				char pw_ss_S[256];
				char pl_ss_S[256];
				
				memset(pw_ss_S , 0x00 , 256);
				memset(pl_ss_S , 0x00 , 256);
				
				fprintf(stderr,"DEBUG: p_size->width = %f\n",p_size->width);
				fprintf(stderr,"DEBUG: p_size->length = %f\n",p_size->length);
				pw_mm = (long)((double)p_size->width * 2540.0 / 72.0);
				pl_mm = (long)((double)p_size->length * 2540.0 / 72.0);

				fprintf(stderr,"DEBUG: pw_mm(ld(before check)) = %ld\n",pw_mm);
				fprintf(stderr,"DEBUG: pl_mm(ld(before check)) = %ld\n",pl_mm);
				
				/* Ver.2.70 : If unit is  "mm" or "cm" , replace pw_mm and pl_mm with lpr command option parameter "p_cups_opt" */
				if( !strcmp( lpr_custom_unit , "mm") && ret >= 0 )		/* unit = mm */
				{
					sscanf( lpr_custom_width , "%ld.%2s" , &pw_mm ,(char *)&pw_ss_S );
					sscanf( lpr_custom_height , "%ld.%2s" , &pl_mm , (char *)&pl_ss_S );

					switch( strlen(pw_ss_S) ){
						case 1:
							pw_mm = (long)(pw_mm * 100 + atol(pw_ss_S) * 10 );
							break;
						case 2:
							pw_mm = (long)(pw_mm * 100 + atol(pw_ss_S) );
							break;
						default:
							pw_mm = (long)(pw_mm * 100 );
							break;
					}
					switch( strlen(pl_ss_S) ){
						case 1:
							pl_mm = (long)(pl_mm * 100 + atol(pl_ss_S) * 10 );
							break;
						case 2:
							pl_mm = (long)(pl_mm * 100 + atol(pl_ss_S) );
							break;
						default:
							pl_mm = (long)(pl_mm * 100 );
							break;
					}

					fprintf(stderr,"DEBUG: unit=mm : pw_mm = %ld , pl_mm = %ld\n",pw_mm,pl_mm);
				}
				else if( !strcmp( lpr_custom_unit , "cm") && ret >= 0 )	/* unit = cm */
				{
					sscanf( lpr_custom_width , "%ld.%3s" , &pw_mm ,(char *)&pw_ss_S );
					sscanf( lpr_custom_height , "%ld.%3s" , &pl_mm , (char *)&pl_ss_S );
					
					switch( strlen(pw_ss_S) ){
						case 1:
							pw_mm = (long)(pw_mm * 1000 + atol(pw_ss_S) * 100 );
							break;
						case 2:
							pw_mm = (long)(pw_mm * 1000 + atol(pw_ss_S) * 10 );
							break;
						case 3:
							pw_mm = (long)(pw_mm * 1000 + atol(pw_ss_S) );
							break;
						default:
							pw_mm = (long)(pw_mm * 1000 );
							break;
					}
					switch( strlen(pl_ss_S) ){
						case 1:
							pl_mm = (long)(pl_mm * 1000 + atol(pl_ss_S) * 100 );
							break;
						case 2:
							pl_mm = (long)(pl_mm * 1000 + atol(pl_ss_S) * 10 );
							break;
						case 3:
							pl_mm = (long)(pl_mm * 1000 + atol(pl_ss_S) );
							break;
						default:
							pl_mm = (long)(pl_mm * 1000 );
							break;
					}
					fprintf(stderr,"DEBUG: unit=cm : pw_mm = %ld , pl_mm = %ld\n",pw_mm,pl_mm);
				}
				
				if( minw_mm != -1 && pw_mm < minw_mm )
					pw_mm = minw_mm;
				if( maxw_mm != -1 && pw_mm > maxw_mm )
					pw_mm = maxw_mm;
				if( minl_mm != -1 && pl_mm < minl_mm )
					pl_mm = minl_mm;
				if( maxl_mm != -1 && pl_mm > maxl_mm )
					pl_mm = maxw_mm;
				snprintf(pw, 255, "%ld", pw_mm);
				snprintf(pl, 255, "%ld", pl_mm);

				fprintf(stderr,"DEBUG: pw_mm(ld) = %ld\n",pw_mm);
				fprintf(stderr,"DEBUG: pl_mm(ld) = %ld\n",pl_mm);

				param_list_add(&p_list, p_table->opt_key, "user", 5);
				param_list_add(&p_list,
					"--paperwidth", pw, strlen(pw) + 1);
				param_list_add(&p_list,
					"--paperheight", pl, strlen(pl) + 1);
			}

			/* Duplex */
			if( !strcmp(p_table->ppd_key, "Duplex") )
			{
				if( !strcmp(choice, "DuplexNoTumble") )
				{
					param_list_add(&p_list, p_table->opt_key,
						LONG_EDGE, strlen(LONG_EDGE) + 1);	//LONG_EDGE	:"--stapleside longside"
				}
				else if( !strcmp(choice, "DuplexTumble") )
				{
					param_list_add(&p_list, p_table->opt_key,
						SHORT_EDGE, strlen(SHORT_EDGE) + 1);
				}
				// Ignore "None" case.
			}
			/* Any other options (include "PageSize" besides "Custom") */
			else
			{
				fprintf(stderr,"DEBUG: (3)Make cif options : choice=%s(p_table->ppd_key=%s)\n",choice,p_table->ppd_key);
				/* this is supposed to fix borderless printing */
				/* to_lower_except_size_X(choice); */
				if( !strcmp(p_table->ppd_key, "PageSize") && is_borderless(choice) )
				{
					fprintf(stderr,"DEBUG: (3)Make cif options : Add borderless(%s)\n",choice);
					param_list_add(&p_list, "--borderless", "", 1);
					borderless_exist = 1;
				}

				/* this is supposed to fix borderless printing */
				to_lower_except_size_X(choice);

				param_list_add(&p_list, p_table->opt_key, choice, strlen(choice) + 1);
			}
		}
		p_table++;
	}

	/* (4)Convert lpr options(in p_cups_opt) to cif options, then append them to p_list */
	/* Vender specific options are also appended to p_list. */
	while( num_opt-- > 0 )	/* num_opt: number of lpr options */
	{
		fprintf(stderr,"DEBUG: ### lpr optins(%d) : %s=%s ###\n" , num_opt,p_cups_opt->name,p_cups_opt->value );

		/* Ver.3.00 position */
		if( !strcmp(p_cups_opt->name, "position"))
		{
		 	if( !strcmp(p_cups_opt->value, "center") ) position_exist = P_CENTER;
			else if( !strcmp(p_cups_opt->value, "top-left") ) position_exist = P_TOPLEFT;
		}

		char *opt_key = ppd_to_opt_key(p_opt_key_table, p_cups_opt->name);
		if( opt_key != NULL )
		{
			char value[256];

			memset(value, 0, 256);
			strncpy(value, p_cups_opt->value, 255);
			to_lower_except_size_X(value);

			fprintf(stderr,"DEBUG: ### lpr optins(%d)(opt_key != NULL) : %s=%s ###\n" ,num_opt,opt_key,value );

			/* Duplex */
			if( !strcmp(p_cups_opt->name, "Duplex") )
			{
				if( !strcasecmp(value, "True") )
					param_list_add(&p_list, opt_key, "", 1);	/* not overwrite */
			}
			else
			{
				/* Ver.2.90Ffor Borderless */
				if( !strcmp(p_cups_opt->name, "PageSize") && is_borderless(value) )
				{
					fprintf(stderr,"DEBUG: (4)Convert lpr options(p_cups_opt) to cif options: Add borderless(%s)\n",value);
					param_list_add(&p_list, "--borderless", "", 1);
					borderless_exist = 1;
				}

				param_list_add(&p_list, opt_key, value, strlen(value) + 1);
			}
		}
		p_cups_opt++;
	}

	/* Ver.3.00 */
	/* If Borderless Printing is OFF : add "--bbox" */
	if( !borderless_exist )
	{
		char bbox_buf[256];
		/* value changed at Ver.3.00 */
		int left   = (int)p_size->left;
		int bottom = (int)p_size->bottom;
		int right  = (int)(p_size->right + 0.99);
		int top    = (int)(p_size->top + 0.99);

		snprintf(bbox_buf, 255, "%-d,%-d,%-d,%-d", left, bottom, right, top);
		param_list_add(&p_list, "--bbox",bbox_buf, strlen(bbox_buf) + 1);
	}

	/* Ver.3.00 */
	/* Add "--fit" (regardless of the Borderless setting) */
	param_list_add(&p_list, "--fit", "", 1);



	/* Ver.3.00 */
	/* "position" existed  : add "--location" */
	if( position_exist ==P_CENTER )
	{
		param_list_add(&p_list, "--location", "center", strlen("center") + 1 );
	}
	else if( position_exist ==P_TOPLEFT )
	{
		param_list_add(&p_list, "--location", "upperleft", strlen("upperleft") + 1 );
	}

	/* Ver.3.20 */
	/* If canon_backend_flag is 1 : add "--bidi" */
	if( canon_backend_flag == 1 )
	{
		param_list_add(&p_list, "--bidi", "", 1 );
	}

	/* Ver.3.50 */
	ParamList *pl = NULL;
	pl = param_list_find(p_param, "CNCopies");
	if ( pl != NULL )
	{
		param_list_add(&p_list, "--copies", pl->value, strlen(pl->value) + 1);
	}

	/* Ver.3.80 */
	/* If rotate_flag -> 1 : "--rotate" */
	if( rotate_flag == 1 ){
		ParamList *plx = NULL;
		plx = param_list_find(p_param, "CNRotate");
		if ( plx != NULL )
		{
			param_list_add(&p_list, "--rotate", plx->value, strlen(plx->value) + 1);
		}
	}
	

	/* Make "cif command" */
	flt_cmd_buf = make_filter_param_line(p_product, reso, p_list);

	if( p_list != NULL ){
		param_list_free(p_list);
		free_opt_key_table(p_opt_key_table);
	}

	ppdClose(p_ppd);

	if( flt_cmd_buf )
	{
		int buf_len;			
		
		buf_len = strlen(gs_cmd_buf) + strlen(flt_cmd_buf) + 1;

		if( (cmd_buf = (char*)malloc(buf_len)) != NULL )
		{
			strcpy(cmd_buf, gs_cmd_buf);
			strcat(cmd_buf, flt_cmd_buf);
		}
		free(flt_cmd_buf);
fprintf(stderr, "pstocanonij: %s\n", cmd_buf);
		return cmd_buf;
	}
	else
		return NULL;
}

int exec_filter(char *cmd_buf, int ofd, int fds[2])
{
	int __attribute__ ((unused)) status = 0;
	int	child_pid = -1;
	char *filter_param[4];
	char shell_buf[256];

	if( pipe(fds) >= 0 )
	{
		child_pid = fork();

		if( child_pid == 0 )
		{

			setpgid(0, 0);
			
			close(0);
			dup2(fds[0], 0);
			close(fds[0]);
			close(fds[1]);

			if( ofd != 1 )
			{
				close(1);
				dup2(ofd, 1);
				close(ofd);
			}

			{

				strcpy(shell_buf, SHELL_PATH);
				strcat(shell_buf, "/");
				strcat(shell_buf, SHELL_NAME);

				filter_param[0] = shell_buf;
				filter_param[1] = "-c";
				filter_param[2] = cmd_buf;
				filter_param[3] = NULL;

				execv(shell_buf, filter_param);
						
				fprintf(stderr, "execl() error\n");
				status = -1;
			}
		}
		else if( child_pid != -1 )
		{
			close(fds[0]);
		}
	}
	return child_pid;
}

static void sigterm_handler(int sigcode)
{
	if( g_filter_pid != -1 )
		kill(-g_filter_pid, SIGTERM);

	g_signal_received = 1;
}

int main(int argc, char *argv[])
{
	cups_option_t *p_cups_opt = NULL;
	int num_opt = 0;
	ParamList *p_ps_param = NULL;
	BufList *p_ps_data = NULL;
	char *p_data_buf;
	int ifd = 0;
	int fds[2];
	struct sigaction sigact;
	char *cmd_buf = NULL;

	char product[256];
#ifdef	DEBUG_SLEEP
	sleep(30);
#endif

	setbuf(stderr, NULL);
	fprintf(stderr, "DEBUG: pstocanonij start.\n");

	memset(&sigact, 0, sizeof(sigact));
	sigact.sa_handler = sigterm_handler;

	if( sigaction(SIGTERM, &sigact, NULL) )
	{
		fputs("ERROR: pstocanonij can't register signal hander.\n", stderr);
		return 1;
	}

	if( argc < 6 || argc > 7 )
	{
		fputs("ERROR: pstocanonij illegal parameter number.\n", stderr);
		return 1;
	}

	if( argv[5] != NULL )
	{
		num_opt = cupsParseOptions(argv[5], 0, &p_cups_opt);
		if( num_opt < 0 )
		{
			fputs("ERROR: illegal option.\n", stderr);
			return 1;
		}
	}

	if( argc == 7 )
	{
		if( (ifd = open(argv[6], O_RDONLY)) == -1 )
		{
			fputs("ERROR: can't open file.\n", stderr);
			return 1;
		}
	}

#ifdef	DEBUG_IN_PS
	g_in_log_fd = open("/tmp/debug_in_log.ps", O_WRONLY);
#endif
	p_ps_param = get_ps_params(ifd, &p_ps_data);

	if( (cmd_buf = make_cmd_param(p_cups_opt, num_opt, p_ps_param, product, 256)) == NULL )
	{
		fputs("ERROR: can't make parameter.\n", stderr);
		goto error_return;
	}

	if( g_signal_received )
		goto error_return;

	if( (p_data_buf = (char*)malloc(DATA_BUF_SIZE)) != NULL )
	{
#ifdef	DEBUG_PS
		int log_fd = open("/tmp/debug_data_log.ps", O_WRONLY);
#endif
		// Execute extended filter.
		g_filter_pid = exec_filter(cmd_buf, 1, fds);

		// Write retained PS header and data.
		buflist_write(p_ps_data, fds[1]);

#ifdef	DEBUG_PS
		buflist_write(p_ps_data, log_fd);
#endif

		// Write remaining PS data.
		while( !g_signal_received )
		{
			int read_bytes = read(ifd, p_data_buf, DATA_BUF_SIZE);

			if( read_bytes > 0 )
			{
				int write_bytes;
				char *p_data = p_data_buf;
#ifdef	DEBUG_PS
				write(log_fd, p_data_buf, read_bytes);
#endif
#ifdef	DEBUG_IN_PS
				if( g_in_log_fd > 0 )
					write(g_in_log_fd, p_data_buf, read_bytes);
#endif
				do
				{
					write_bytes = write(fds[1], p_data, read_bytes);

					if( write_bytes < 0 )
					{
						if( errno == EINTR )
							continue;
						fprintf(stderr,
							"ERROR: pstocanonij write error,%d.\n", errno);
						goto error_exit;
					}
					read_bytes -= write_bytes;
					p_data += write_bytes;
				}
				while( !g_signal_received && read_bytes > 0 );
			}
			else if( read_bytes < 0 )
			{
				if( errno == EINTR )
					continue;
				fprintf(stderr, "ERROR: pstocanonij read error,%d.\n", errno);
				goto error_exit;
			}
			else
				break;
		}

		free(p_data_buf);

#ifdef	DEBUG_PS
		if( log_fd != -1 ) close(log_fd);
#endif
	}

#ifdef	DEBUG_IN_PS
	if( g_in_log_fd > 0 )
		close(g_in_log_fd);
#endif

	free(cmd_buf);

	if( p_ps_param != NULL )
		param_list_free(p_ps_param);
	if( p_ps_data != NULL )
		buflist_destroy(p_ps_data);
	if( ifd != 0 )
		close(ifd);

	close(fds[1]);

	if( g_filter_pid != -1 ) { 
		waitpid(g_filter_pid, NULL, 0); /* Ver.3.80 */
	}

	return 0;

error_exit:
	if( p_data_buf != NULL )
		free(p_data_buf);

error_return:
	free(cmd_buf);

	if( p_ps_param != NULL )
		param_list_free(p_ps_param);
	if( p_ps_data != NULL )
		buflist_destroy(p_ps_data);
	if( ifd != 0 )
		close(ifd);

	return 1;
}
