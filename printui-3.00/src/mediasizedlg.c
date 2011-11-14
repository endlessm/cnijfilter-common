/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2008
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
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
#include <string.h>
#include <ctype.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


static const gchar* recommend_item_button_name[RECOMMEND_ITEM_NUM + 1] =
{
	"mediasize_recommend_radio_button1",
	"mediasize_recommend_radio_button2",
	"mediasize_recommend_radio_button3",
	"mediasize_recommend_radio_button4",
	NULL
};

static const gchar* illegal_select_item_button_name[ILLEGAL_SELECT_ITEM_NUM + 1] =
{
	"mediasize_illegal_select_radio_button1",
	"mediasize_illegal_select_radio_button2",
	"mediasize_illegal_select_radio_button3",
	"mediasize_illegal_select_radio_button4",
	NULL
};

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
		dialog->item_value[0] = KeyToValue(CNCL_PAPERSIZE, applied);
		dialog->item_count = 1;

		size = ValueToName(CNCL_PAPERSIZE, dialog->item_value[0]);
	}
	else if( dialog->change == UI_MEDIASIZE_CHANGE_MEDIA )
	{
		dialog->item_value[0] = KeyToValue(CNCL_MEDIATYPE, applied);
		dialog->item_count = 1;

		media = ValueToName(CNCL_MEDIATYPE, dialog->item_value[0]);
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

int ShowMediaSizeRecommendDialog(UIMediaSizeDialog* dialog, gchar* applied)
{
	GtkWidget* current_size_label;
	GtkWidget* current_media_label;
	GtkWidget* message_label;
	GtkButton* button[RECOMMEND_ITEM_NUM];
	char* media;
	char* size;
	short change_id;
	char* change_msg;
	int i;


	// Current paper size.
	current_size_label = LookupWidget(UI_DIALOG(dialog)->window,
							"mediasize_recommend_current_size_label");
	size = ValueToName(CNCL_PAPERSIZE,
						KeyToValue(CNCL_PAPERSIZE, dialog->size));
	gtk_label_set_text(GTK_LABEL(current_size_label), size);

	// Current media type.
	current_media_label = LookupWidget(UI_DIALOG(dialog)->window,
							"mediasize_recommend_current_media_label");
	media = ValueToName(CNCL_MEDIATYPE,
						KeyToValue(CNCL_MEDIATYPE, dialog->media));
	gtk_label_set_text(GTK_LABEL(current_media_label), media);

	dialog->item_count = CountWords(applied);

	for( i = 0 ; i < RECOMMEND_ITEM_NUM ; i++ )
	{
		button[i] = (GtkButton*)LookupWidget(UI_DIALOG(dialog)->window,
												recommend_item_button_name[i]);
		gtk_widget_hide(GTK_WIDGET(button[i]));
	}
	
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
		gchar* alert_msg1_1
			= LookupText(g_keytext_list, "mediasize_recommend_message1_1");
		gchar* alert_msg1_2
			= LookupText(g_keytext_list, "mediasize_recommend_message1_2");
		gchar* change_to
			= LookupText(g_keytext_list, applied);
		gchar* message
			= (gchar*)g_malloc(strlen(change_msg) + strlen(alert_msg1_1) +
				strlen(alert_msg1_2) +strlen(change_to) +2 );	/* Ver.2.80 "2":\n+\0 */
		gchar* tmp_message
			= (gchar*)g_malloc(strlen(change_msg) + strlen(change_to) + strlen(alert_msg1_1) + 1 );	/* Ver.2.80 "1":\0 */

		sprintf(tmp_message, alert_msg1_1, change_msg, change_to);
		sprintf(message, "%s\n%s", tmp_message, alert_msg1_2);
		gtk_label_set_text(GTK_LABEL(message_label), message);

		g_free(tmp_message);
		g_free(message);

		dialog->item_value[0] = KeyToValue(change_id, applied);
	}
	// In case of changing more than 1 recommended items.
	else
	{
		gchar* alert_msg2_1
			= LookupText(g_keytext_list, "mediasize_recommend_message2_1");
		gchar* alert_msg2_2
			= LookupText(g_keytext_list, "mediasize_recommend_message2_2");
		gchar* alert_msg2_3
			= LookupText(g_keytext_list, "mediasize_recommend_message2_3");
			
		gchar* message
			= (gchar*)g_malloc(strlen(change_msg) + strlen(alert_msg2_1) + strlen(alert_msg2_2) + strlen(alert_msg2_3) +3 );	/* "3":\n+\n+\0 */
		gchar* tmp_message
			= (gchar*)g_malloc(strlen(change_msg) + strlen(alert_msg2_1) +1 );/* "1":\0 */

		sprintf(tmp_message, alert_msg2_1, change_msg );
		sprintf(message, "%s\n%s\n%s", tmp_message, alert_msg2_2,alert_msg2_3);
		gtk_label_set_text(GTK_LABEL(message_label), message);

		g_free(tmp_message);
		g_free(message);

		{
			gchar* words = applied;
			gchar* word = (gchar*)g_malloc(strlen(words));
			gchar* next;
			gchar* change_to;
			int len;

			for( i = 0 ; i < dialog->item_count ; i++ )
			{
				next = GetWord(words, &len);
				strncpy(word, words, len);
				word[len] = '\0';
				change_to = LookupText(g_keytext_list, word);

//				gtk_label_set_text(GTK_BIN(button[i]->child), change_to);
				gtk_label_set_text(GTK_LABEL(GTK_BIN(button[i])->child), change_to);
				if( i == 0 )
					gtk_toggle_button_set_active(
						GTK_TOGGLE_BUTTON(button[i]), TRUE);

				gtk_widget_show(GTK_WIDGET(button[i]));

				dialog->item_value[i] = KeyToValue(change_id, word);

				words = next;
			}
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

int ShowMediaSizeIllegalSelectDialog(UIMediaSizeDialog* dialog, gchar* applied)
{
	GtkWidget* current_size_label;
	GtkWidget* current_media_label;
	GtkWidget* message_label;
	GtkButton* button[RECOMMEND_ITEM_NUM];
	char* media;
	char* size;
	short change_id;
	char* change_msg;
	int i;
	gchar* alert_msg2_1;
	gchar* alert_msg2_2;
	gchar* message;
	gchar* tmp_message;

	// Current paper size.
	current_size_label = LookupWidget(UI_DIALOG(dialog)->window,
							"mediasize_illegal_select_current_size_label");
	size = ValueToName(CNCL_PAPERSIZE,
						KeyToValue(CNCL_PAPERSIZE, dialog->size));
	gtk_label_set_text(GTK_LABEL(current_size_label), size);

	// Current media type.
	current_media_label = LookupWidget(UI_DIALOG(dialog)->window,
							"mediasize_illegal_select_current_media_label");
	media = ValueToName(CNCL_MEDIATYPE,
						KeyToValue(CNCL_MEDIATYPE, dialog->media));
	gtk_label_set_text(GTK_LABEL(current_media_label), media);

	dialog->item_count = CountWords(applied);

	for( i = 0 ; i < RECOMMEND_ITEM_NUM ; i++ )
	{
		button[i] = (GtkButton*)LookupWidget(UI_DIALOG(dialog)->window,
												illegal_select_item_button_name[i]);
		gtk_widget_hide(GTK_WIDGET(button[i]));
	}
	
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
	message
		= (gchar*)g_malloc(strlen(change_msg) + strlen(alert_msg2_1) + strlen(alert_msg2_2) +2 );	/* Ver.2.80 "2":\n+\0 */
	tmp_message
		= (gchar*)g_malloc(strlen(change_msg) + strlen(alert_msg2_1) +1 );	/* Ver.2.80 "1":\0 */

	sprintf(tmp_message, alert_msg2_1, change_msg );
	sprintf(message, "%s\n%s", tmp_message, alert_msg2_2);
	gtk_label_set_text(GTK_LABEL(message_label), message);

	g_free(tmp_message);
	g_free(message);

	{
		gchar* words = applied;
		gchar* word = (gchar*)g_malloc(strlen(words));
		gchar* next;
		gchar* change_to;
		int len;

		for( i = 0 ; i < dialog->item_count ; i++ )
		{
			next = GetWord(words, &len);
			strncpy(word, words, len);
			word[len] = '\0';
			change_to = LookupText(g_keytext_list, word);

//			gtk_label_set_text(GTK_LABEL(button[i]->child), change_to);
			gtk_label_set_text(GTK_LABEL(GTK_BIN(button[i])->child), change_to);
			if( i == 0 )
				gtk_toggle_button_set_active(
					GTK_TOGGLE_BUTTON(button[i]), TRUE);

			gtk_widget_show(GTK_WIDGET(button[i]));

			dialog->item_value[i] = KeyToValue(change_id, word);

			words = next;
		}
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
				int index;

				if( dialog->item_count > 1 )
				{
					if( table->type == UI_MEDIASIZE_RECOMMEND )
					{
						index = GetActiveButtonIndex(UI_DIALOG(dialog)->window,
										 recommend_item_button_name, 0);
					}
					else
					{
						index = GetActiveButtonIndex(UI_DIALOG(dialog)->window,
										 illegal_select_item_button_name, 0);
					}
				}
				else
					index = 0;

				if( dialog->change == UI_MEDIASIZE_CHANGE_SIZE )
					UpdateMenuLink(CNCL_PAPERSIZE, dialog->item_value[index]);
				else
				{
					// Save current supply value.
					short supply_value = GetCurrentnValue(CNCL_MEDIASUPPLY);

					// Change the media type.
					UpdateMenuLink(CNCL_MEDIATYPE, dialog->item_value[index]);

					if( supply_value != GetCurrentnValue(CNCL_MEDIASUPPLY) )
					{
						// If no supply value for the current media type,
						// Some alert should be shown.

						// Only restore the saved supply value in this version.
						UpdateMenuLink(CNCL_MEDIASUPPLY, supply_value);
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


