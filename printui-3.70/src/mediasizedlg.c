/*  Canon Inkjet Printer Driver for Linux
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


//#ifdef HAVE_CONFIG_H
//#  include <config.h>
//#endif

#include <gtk/gtk.h>
#ifdef	USE_LIB_GLADE
#	include <glade/glade.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


static char* GetWord(char* words, int* len)
{
	char* head = words;
	char* next = NULL;
	int count = 0;

	while( *head )
	{
		if( !isspace(*head) )
			break;
		head++;
	}
	if( *head )
	{
		char* tail = head;
		while( *tail )
		{
			if( isspace(*tail) || *tail == '\0' )
				break;
			tail++;
			count++;
		}

		next = tail;
		while( *next )
		{
			if( !isspace(*next) )
				break;
			next++;
		}
		if( *next == '\0' )
			next = NULL;
	}
	*len = count;
	return next;
}

static char* SearchWord(char* str, char* words)
{
	int len;
	char* next;

	while( words != NULL )
	{
		next = GetWord(words, &len);
		if( !strncmp(str, words, len) )
			break;

		words = next;
	}
	return words;
}

static int CountWords(char* words)
{
	int len;
	int count = 0;

	while( words != NULL )
	{
		words = GetWord(words, &len);
		count++;
	}

	return count;
}

static gchar* GetAvailableSize(gchar* applied)
{
	gchar* words = applied;
	gchar* word = (gchar*)g_malloc(strlen(words) + 1);
	gchar* result = (gchar*)g_malloc(strlen(words) + 2);
	gchar* next;
	int len;
	short paper_size_value;

	result[0] = '\0';

	while( words != NULL )
	{
		next = GetWord(words, &len);
		strncpy(word, words, len);
		word[len] = '\0';

		paper_size_value = KeyToValue(CNCL_PAPERSIZE, word);

		if( IsAvailableValue(CNCL_PAPERSIZE, paper_size_value) )
		{
			strcat(result, word);
			strcat(result, " ");
		}
		words = next;
	}

	g_free(word);

	if( (len = strlen(result)) > 0 )
		result[len - 1] = '\0';	// Delete last space.
	return result;
}

static gchar* GetAvailableMedia(gchar* applied)
{
	short cartridge_type_value = GetCurrentnValue(CNCL_CARTRIDGE);
	gchar* words = applied;
	gchar* word = (gchar*)g_malloc(strlen(words) + 1);
	gchar* result = (gchar*)g_malloc(strlen(words) + 2);
	gchar* next;
	int len;
	short media_type_value;

	result[0] = '\0';

	while( words != NULL )
	{
		next = GetWord(words, &len);
		strncpy(word, words, len);
		word[len] = '\0';

		media_type_value = KeyToValue(CNCL_MEDIATYPE, word);

		if( IsAvailableMedia(g_mediatype_dialog,
				media_type_value, cartridge_type_value) )
		{
			strcat(result, word);
			strcat(result, " ");
		}
		words = next;
	}

	g_free(word);

	if( (len = strlen(result)) > 0 )
		result[len - 1] = '\0';	// Delete last space.

	return result;
}

UIMediaSizeDialog* CreateMediaSizeDialog(
				UIDialog* parent, MediaSizeDlgType type)
{
	GtkWidget* window = NULL;
	UIMediaSizeDialog* dialog = NULL;

	switch( type )
	{
	case UI_MEDIASIZE_DLG_ILLEGAL:
#ifdef	USE_LIB_GLADE
		window = LookupWidget(NULL, "mediasize_illegal_dialog");
#else
		window = create_mediasize_illegal_dialog();
#endif
		break;

	case UI_MEDIASIZE_DLG_RECOMMEND:
#ifdef	USE_LIB_GLADE
		window = LookupWidget(NULL, "mediasize_recommend_dialog");
#else
		window = create_mediasize_recommend_dialog();
#endif
		break;

	case UI_MEDIASIZE_DLG_ILLEGAL_SELECT:
#ifdef	USE_LIB_GLADE
		window = LookupWidget(NULL, "mediasize_illegal_select_dialog");
#else
		window = create_mediasize_illegal_select_dialog();
#endif
		break;

	default:
		break;
	}

	if( window )
	{
		dialog = (UIMediaSizeDialog*)CreateDialog(
					sizeof(UIMediaSizeDialog), parent);
		UI_DIALOG(dialog)->window = window;
	}

	return dialog;
}

int ShowMediaSizeIllegalDialog(UIMediaSizeDialog* dialog, gchar* applied)
{
	GtkWidget* current_size_label;
	GtkWidget* current_media_label;
	GtkWidget* recommend_size_label;
	GtkWidget* recommend_media_label;
	char* media;
	char* size;

	// Current paper size.
	current_size_label = LookupWidget(UI_DIALOG(dialog)->window,
				"mediasize_illegal_current_size_label");
	size = ValueToName(CNCL_PAPERSIZE,
				KeyToValue(CNCL_PAPERSIZE, dialog->size));
	gtk_label_set_text(GTK_LABEL(current_size_label), size);

	// Current media type.
	current_media_label = LookupWidget(UI_DIALOG(dialog)->window,
				"mediasize_illegal_current_media_label");
	media = ValueToName(CNCL_MEDIATYPE,
				KeyToValue(CNCL_MEDIATYPE, dialog->media));
	gtk_label_set_text(GTK_LABEL(current_media_label), media);

	recommend_size_label = LookupWidget(UI_DIALOG(dialog)->window,
				"mediasize_illegal_recommend_size_label");
	recommend_media_label = LookupWidget(UI_DIALOG(dialog)->window,
				"mediasize_illegal_recommend_media_label");

	if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )
	{
		// Display recommended paper size.
		dialog->current_change_to_id = KeyToValue(CNCL_PAPERSIZE, applied);		/* Ver.3.20:default current...set top item */
		
		dialog->item_count = 1;

		size = ValueToName(CNCL_PAPERSIZE, dialog->current_change_to_id);	/* Ver.3.20 */
	}
	else if( dialog->change == UI_MEDIASIZE_CHANGE_MEDIA )
	{
		dialog->current_change_to_id = KeyToValue(CNCL_MEDIATYPE, applied);		/* Ver.3.20:default current...set top item */

		dialog->item_count = 1;

		media = ValueToName(CNCL_MEDIATYPE, dialog->current_change_to_id);		/* Ver.3.20 */
	}

	gtk_label_set_text(GTK_LABEL(recommend_size_label), size);
	gtk_label_set_text(GTK_LABEL(recommend_media_label), media);

	gtk_window_set_title(
		GTK_WINDOW(UI_DIALOG(dialog)->window), g_window_title);	
	gtk_window_set_position(
		GTK_WINDOW(UI_DIALOG(dialog)->window), GTK_WIN_POS_CENTER);	

	ShowDialog((UIDialog*)dialog, "mediasize_illegal_apply_button");
	return dialog->exec;
}


/* ver.3.20:Use combo (item list) */
int ShowMediaSizeRecommendDialog(UIMediaSizeDialog* dialog, gchar* applied)
{
	GtkWidget* current_label;
	GtkWidget* message_label;
	char* data;
	short change_id;
	char* change_msg;
	int i;

	if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE ){
		/* show  media -> size */
		/* show media */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label001");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_MAIN_IDC_STT_MEDIATYPE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label002");
		data = ValueToName(CNCL_MEDIATYPE, KeyToValue(CNCL_MEDIATYPE, dialog->media));
		gtk_label_set_text( GTK_LABEL(current_label), data );

		/* show size */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label003");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_PAGESET_XP_IDC_STT_PAGESIZE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label004");
		data = ValueToName(CNCL_PAPERSIZE, KeyToValue(CNCL_PAPERSIZE, dialog->size));
		gtk_label_set_text( GTK_LABEL(current_label), data );
	}
	else {
		/* show  size -> media */
		/* show size */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label001");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_PAGESET_XP_IDC_STT_PAGESIZE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label002");
		data = ValueToName(CNCL_PAPERSIZE, KeyToValue(CNCL_PAPERSIZE, dialog->size));
		gtk_label_set_text( GTK_LABEL(current_label), data );

		/* show media */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label003");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_MAIN_IDC_STT_MEDIATYPE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_label004");
		data = ValueToName(CNCL_MEDIATYPE, KeyToValue(CNCL_MEDIATYPE, dialog->media));
		gtk_label_set_text( GTK_LABEL(current_label), data );
	}
	dialog->item_count = CountWords(applied);


	message_label = LookupWidget(UI_DIALOG(dialog)->window,
									"mediasize_recommend_message_label");

	if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )
	{
		change_id = CNCL_PAPERSIZE;
		change_msg = LookupText(g_keytext_list, "mediasize_change_size");
	}
	else
	{
		change_id = CNCL_MEDIATYPE;
		change_msg = LookupText(g_keytext_list, "mediasize_change_media");
	}


	// In case of changing only 1 recommended item.
	if( dialog->item_count == 1 )
	{
#ifdef _PRINTUI_DEBUG_
fprintf(stderr,"ShowMediaSizeRecommendDialog:4\n");
#endif
		gint message_len, tmp_message_len;
		gchar* alert_msg1_1
			= LookupText(g_keytext_list, "mediasize_recommend_message1_1");
		gchar* alert_msg1_2
			= LookupText(g_keytext_list, "mediasize_recommend_message1_2");
		gchar* change_to
			= LookupText(g_keytext_list, applied);
		message_len = strlen(change_msg) + strlen(alert_msg1_1) + strlen(alert_msg1_2) +strlen(change_to) + 2;
		gchar* message = (gchar*)g_malloc( message_len );
		tmp_message_len = strlen(change_msg) + strlen(change_to) + strlen(alert_msg1_1) + 1;
		gchar* tmp_message = (gchar*)g_malloc( tmp_message_len );

		snprintf(tmp_message, tmp_message_len, alert_msg1_1, change_msg, change_to); /* Ver.3.60 */
		snprintf(message, message_len, "%s\n%s", tmp_message, alert_msg1_2);
		gtk_label_set_text(GTK_LABEL(message_label), message);

		g_free(tmp_message);
		g_free(message);

		dialog->current_change_to_id = KeyToValue(change_id, applied);		/* Ver.3.20:default current...set top item */
		
		/* Ver.3.20: 1 item -> Hide combo */
		gtk_widget_hide( GTK_WIDGET( LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_combo" ) ) );
		
		
	}

	// In case of changing more than 1 recommended items.
	else
	{
		gint message_len, tmp_message_len;
		gchar* alert_msg2_1
			= LookupText(g_keytext_list, "mediasize_recommend_message2_1");
		gchar* alert_msg2_2
			= LookupText(g_keytext_list, "mediasize_recommend_message2_2");
		gchar* alert_msg2_3
			= LookupText(g_keytext_list, "mediasize_recommend_message2_3");
			
		message_len = strlen(change_msg) + strlen(alert_msg2_1) + strlen(alert_msg2_2) + strlen(alert_msg2_3) + 3; /* "3":\n+\n+\0 */
		gchar* message = (gchar*)g_malloc( message_len );
		tmp_message_len = strlen(change_msg) + strlen(alert_msg2_1) + 1;/* "1":\0 */
		gchar* tmp_message = (gchar*)g_malloc( tmp_message_len );

		snprintf(tmp_message, tmp_message_len, alert_msg2_1, change_msg ); /* Ver.3.60 */
		snprintf(message, message_len, "%s\n%s\n%s", tmp_message, alert_msg2_2,alert_msg2_3);
		gtk_label_set_text(GTK_LABEL(message_label), message);

		g_free(tmp_message);
		g_free(message);

		{
			gchar* words = applied;
			gchar* word = (gchar*)g_malloc(strlen(words));
			gchar* next;
			gchar* change_to;
			int len;
			
			/* Ver.3.20: make combo */
			GtkWidget* combo = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_recommend_combo" );
		
			/* Remove all items in current list */
			if(gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ){
				while( 1 ){
					gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), 0 );
					if( ! gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ) break;
					gtk_combo_box_remove_text( GTK_COMBO_BOX( combo ), 0 );
				}
			}
			/* Add available list (not disable items from UIDB ) */
			for( i = 0 ; i < dialog->item_count ; i++ )
			{
				next = GetWord(words, &len);
				strncpy(word, words, len);
				word[len] = '\0';
				change_to = LookupText(g_keytext_list, word);
			
				if( change_to != NULL )
				{
					if( *change_to != '\0' ){
						/* append one item */
						gtk_combo_box_append_text( GTK_COMBO_BOX( combo ), change_to );
					}
				}
				
				if( i == 0) dialog->current_change_to_id = KeyToValue(change_id, word);		/* default current...set top item */
				
				words = next;
				
			}
			/* Set active item to top */
			gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), 0 );
			gtk_widget_show( combo );
			
			g_free(word);
		}
	}

	gtk_window_set_title(
		GTK_WINDOW(UI_DIALOG(dialog)->window), g_window_title);	
	gtk_window_set_position(
		GTK_WINDOW(UI_DIALOG(dialog)->window), GTK_WIN_POS_CENTER);	

	ShowDialog((UIDialog*)dialog, "mediasize_recommend_apply_button");

	return dialog->exec;
}

/* ver.3.20:Use combo (item list) */
int ShowMediaSizeIllegalSelectDialog(UIMediaSizeDialog* dialog, gchar* applied)
{
	GtkWidget* current_label;
	GtkWidget* message_label;
	char *data;
	short change_id;
	char* change_msg;
	int i;
	gchar* alert_msg2_1;
	gchar* alert_msg2_2;
	gchar* message;
	gchar* tmp_message;
	gint message_len, tmp_message_len;

	if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE ){
		/* show  media -> size */
		/* show media */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label001");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_MAIN_IDC_STT_MEDIATYPE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label002");
		data = ValueToName(CNCL_MEDIATYPE, KeyToValue(CNCL_MEDIATYPE, dialog->media));
		gtk_label_set_text( GTK_LABEL(current_label), data );

		/* show size */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label003");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_PAGESET_XP_IDC_STT_PAGESIZE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label004");
		data = ValueToName(CNCL_PAPERSIZE, KeyToValue(CNCL_PAPERSIZE, dialog->size));
		gtk_label_set_text( GTK_LABEL(current_label), data );
	}
	else {
		/* show  size -> media */
		/* show size */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label001");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_PAGESET_XP_IDC_STT_PAGESIZE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label002");
		data = ValueToName(CNCL_PAPERSIZE, KeyToValue(CNCL_PAPERSIZE, dialog->size));
		gtk_label_set_text( GTK_LABEL(current_label), data );

		/* show media */
		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label003");
		gtk_label_set_text( GTK_LABEL(current_label), LookupText(g_keytext_list, "LUM_IDD_PAG_MAIN_IDC_STT_MEDIATYPE") );

		current_label = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_select_label004");
		data = ValueToName(CNCL_MEDIATYPE, KeyToValue(CNCL_MEDIATYPE, dialog->media));
		gtk_label_set_text( GTK_LABEL(current_label), data );
	}
	dialog->item_count = CountWords(applied);

	message_label = LookupWidget(UI_DIALOG(dialog)->window,
									"mediasize_illegal_select_message_label");
	if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )
	{
		change_id = CNCL_PAPERSIZE;
		change_msg = LookupText(g_keytext_list, "mediasize_change_size");
	}
	else
	{
		change_id = CNCL_MEDIATYPE;
		change_msg = LookupText(g_keytext_list, "mediasize_change_media");
	}

	// In case of changing more than 1 recommended items.
	alert_msg2_1
		= LookupText(g_keytext_list, "mediasize_illegal_select_message2_1");
	alert_msg2_2
		= LookupText(g_keytext_list, "mediasize_illegal_select_message2_2");
	message_len = strlen(change_msg) + strlen(alert_msg2_1) + strlen(alert_msg2_2) + 2;	/* Ver.2.80 "2":\n+\0 */
	message = (gchar*)g_malloc( message_len );
	tmp_message_len = strlen(change_msg) + strlen(alert_msg2_1) + 1;	/* Ver.2.80 "1":\0 */
	tmp_message = (gchar*)g_malloc( tmp_message_len );

	snprintf(tmp_message, tmp_message_len, alert_msg2_1, change_msg ); /* Ver.3.60 */
	snprintf(message, message_len, "%s\n%s", tmp_message, alert_msg2_2);
	gtk_label_set_text(GTK_LABEL(message_label), message);

	g_free(tmp_message);
	g_free(message);

	{
		gchar* words = applied;
		gchar* word = (gchar*)g_malloc(strlen(words));
		gchar* next;
		gchar* change_to;
		int len;

		/* Ver.3.20: make combo */
		GtkWidget* combo = LookupWidget(UI_DIALOG(dialog)->window, "mediasize_illegal_combo" );
	
		/* Remove all items in current list */
		if(gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ){
			while( 1 ){
				gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), 0 );
				if( ! gtk_combo_box_get_active_text( GTK_COMBO_BOX( combo )) ) break;
				gtk_combo_box_remove_text( GTK_COMBO_BOX( combo ), 0 );
			}
		}
		/* Add available list (not disable items from UIDB ) */
		for( i = 0 ; i < dialog->item_count ; i++ )
		{
			next = GetWord(words, &len);
			strncpy(word, words, len);
			word[len] = '\0';
			change_to = LookupText(g_keytext_list, word);
			
			if( change_to != NULL )
			{
				if( *change_to != '\0' ){
					/* append one item */
					gtk_combo_box_append_text( GTK_COMBO_BOX( combo ), change_to );
				}
			}
			
			if( i == 0) dialog->current_change_to_id = KeyToValue(change_id, word);		/* default current...set top item */
			
			words = next;
			
		}
		/* Set active item to top */
		gtk_combo_box_set_active( GTK_COMBO_BOX( combo ), 0 );
		gtk_widget_show( combo );

		g_free(word);
	}

	gtk_window_set_title(
		GTK_WINDOW(UI_DIALOG(dialog)->window), g_window_title);	
	gtk_window_set_position(
		GTK_WINDOW(UI_DIALOG(dialog)->window), GTK_WIN_POS_CENTER);	

	ShowDialog((UIDialog*)dialog, "mediasize_illegal_select_apply_button");
	return dialog->exec;
}

void HideMediaSizeDialog(UIMediaSizeDialog* dialog,
							gboolean exec, gboolean apply)
{
	// Set exec flag.
	dialog->exec = exec;

	// Set apply flag.
	dialog->apply = apply;

	HideDialog((UIDialog*)dialog);
}

gboolean CheckMediaSizeCombination(LPBJFLTDEVICE bjdev, gboolean* change_item)
{
	MediaSizeTable* table = GetMediaSizeTable(bjdev->bjfltModelID);
	char* media = ValueToKey(CNCL_MEDIATYPE, bjdev->bjfltMediaType);
	char* size = ValueToKey(CNCL_PAPERSIZE, bjdev->bjfltPaperSize);
	int change;
	gboolean exec_print;
	int result = TRUE;
	gchar* applied = NULL;
	gchar* applied_title = NULL;
	GtkWidget *window = UI_DIALOG(g_main_window)->window;

	*change_item = FALSE;

	if( table == NULL )
		return TRUE;


	while( table->base != NULL )
	{
		if( !strcmp(media, table->base) )
		{
			// Get available media size.
			applied = GetAvailableSize(table->applied);

			if( SearchWord(size, applied) == NULL )
			{
				applied_title = GetAvailableSize(table->applied_title);
				change = UI_MEDIASIZE_CHANGE_SIZE;
				break;
			}
		}
		else if( !strcmp(size, table->base) )
		{
			// Get available media type.
			applied = GetAvailableMedia(table->applied);

			if( SearchWord(media, applied) == NULL )
			{
				applied_title = GetAvailableMedia(table->applied_title);
				change = UI_MEDIASIZE_CHANGE_MEDIA;
				break;
			}
		}
		table++;
	}


	if( table->base )
	{
		UIMediaSizeDialog* dialog = NULL;
		int (*show_dialog)(UIMediaSizeDialog*, gchar*) = NULL;

		switch( table->type )
		{
			case UI_MEDIASIZE_ILLEGAL:
				if( 1 >= CountWords(applied) )
				{
					dialog = g_mediasize_illegal_dialog;
					show_dialog = ShowMediaSizeIllegalDialog;
				}
				else
				{
					dialog = g_mediasize_illegal_select_dialog;
					show_dialog = ShowMediaSizeIllegalSelectDialog;
				}
				break;

			case UI_MEDIASIZE_RECOMMEND:
				dialog = g_mediasize_recommend_dialog;
				show_dialog = ShowMediaSizeRecommendDialog;
				break;
		}

		// Show the dialog when the number of applied item is more than 1.
		if( dialog && strlen(applied) > 0 )
		{
			dialog->media = media;
			dialog->size = size;
			dialog->table = (void*)table;
			dialog->change = change;

			// Show dialog.
			exec_print = show_dialog(dialog, applied_title);

			if( dialog->apply )
			{
				GtkWidget*	analyzer_combo = NULL;
				char 		*change_to_value_str = NULL;
				short		change_to_id;

				if( dialog->item_count > 1 )		/* multiple items -> get value id of chenge item */
				{
					/* Ver.3.20 */
					if( table->type == UI_MEDIASIZE_RECOMMEND )			/* recommend */
						analyzer_combo = LookupWidget(UI_DIALOG(dialog)->window,  "mediasize_recommend_combo");
					else												/* illegal   */
						analyzer_combo = LookupWidget(UI_DIALOG(dialog)->window,  "mediasize_illegal_combo");

					change_to_value_str = (char*)gtk_combo_box_get_active_text(GTK_COMBO_BOX(analyzer_combo));
					
					if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )	/* change size */
						change_to_id = NameToValue( CNCL_PAPERSIZE , change_to_value_str );
					else												/* change media */
						change_to_id = NameToValue( CNCL_MEDIATYPE , change_to_value_str );
					
					dialog->current_change_to_id = change_to_id;
					
					if(change_to_value_str){
						free(change_to_value_str);
						change_to_value_str = NULL;
					}
				}

				if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )
				{
					UpdateMenuLink(CNCL_PAPERSIZE, dialog->current_change_to_id);
					DisableSignal();
					UpdateWidgets(window, NULL);
					EnableSignal();
				}
				else
				{
					// Save current supply value.
					short supply_value = GetCurrentnValue(CNCL_MEDIASUPPLY);

					// Change the media type.
					UpdateMenuLink(CNCL_MEDIATYPE, dialog->current_change_to_id);
					DisableSignal();
					UpdateWidgets(window, NULL);
					EnableSignal();

					if( supply_value != GetCurrentnValue(CNCL_MEDIASUPPLY) )
					{
						// If no supply value for the current media type,
						// Some alert should be shown.

						// Only restore the saved supply value in this version.
						//UpdateMenuLink(CNCL_MEDIASUPPLY, supply_value);
					}
				}

				*change_item = TRUE;
			}
			result = exec_print;
		}
	}

	if( applied )
		g_free(applied);

	if( applied_title )
		g_free(applied_title);	/* Ver.3.00 */

	return result;
}



/* Ver.2.80 */
/*--- illegal ---*/
gboolean
on_mediasize_illegal_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
	return TRUE;
}


void
on_mediasize_illegal_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_dialog;
	
	HideMediaSizeDialog( dialog , TRUE, TRUE);
}


void
on_mediasize_illegal_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
}



/*--- illegal_select ---*/
gboolean
on_mediasize_illegal_select_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_select_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
	return TRUE;
}


void
on_mediasize_illegal_select_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_select_dialog;
	
	HideMediaSizeDialog( dialog , TRUE, TRUE);
}


void
on_mediasize_illegal_select_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_illegal_select_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
}



/*--- recommend ---*/
gboolean
on_mediasize_recommend_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_recommend_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
	return TRUE;
}


void
on_mediasize_recommend_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_recommend_dialog;
	
	HideMediaSizeDialog( dialog , TRUE, TRUE);
}


void
on_mediasize_recommend_not_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_recommend_dialog;
	
	HideMediaSizeDialog( dialog , TRUE, FALSE);
}


void
on_mediasize_recommend_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	UIMediaSizeDialog* dialog = g_mediasize_recommend_dialog;
	
	HideMediaSizeDialog( dialog , FALSE, FALSE);
}


