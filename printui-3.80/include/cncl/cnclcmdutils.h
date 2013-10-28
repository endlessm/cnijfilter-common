/*
 *  Canon Inkjet Printer Driver for Linux
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
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
*/



#ifndef __IVECUTILS_H__
#define __IVECUTILS_H__


/*
 *   parameter ID
 */
#define CNCL_CHECK_START1		(1)
#define CNCL_CHECK_START2		(2)
#define CNCL_CHECK_END			(3)
#define CNCL_CHECK_DATA			(4)
#define CNCL_CHECK_POWERON		(5)

#define CNCL_COMMAND_POWEROFF	(11)
#define CNCL_COMMAND_POWERON	(12)

#define CNCL_COMMAND_START1		(21)
#define CNCL_COMMAND_START2		(22)
#define CNCL_COMMAND_END		(23)

#define CNCL_MAKECOMMAND_BUF_LEN	(1024)


/*
 *   prototypes
 */
extern CNCLErr CNCL_MakePrintCommand ( short operation_id , char *out_data_buf , short out_buf_len , char *id_str , char *bidi );
extern CNCLErr CNCL_MakeDeviceCommand( short operation_id , char *out_data_buf , short out_buf_len  );
extern CNCLErr CNCL_CheckPrintCommand( short operation_id , char *in_data_buf , short in_data_size  , char *id_str_buf , short id_buf_len );
extern CNCLErr CNCL_GetStatusCommand  ( char *in_data_buf , short in_data_size , char *out_data_buf , short out_buf_len , short *out_data_size );
extern CNCLErr CNCL_SetSSRDef        ( char *in_data_buf  , short *data_size );
extern CNCLErr CNCL_SetImageDirection( char  *in_data_buf, short *data_size, short direction);

#endif	/* __IVECUTILS_H__ */
