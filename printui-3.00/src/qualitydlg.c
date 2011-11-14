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

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif
#include <stdio.h>

#include "bjuidefs.h"


static const gchar* print_quality_button_name[] =
{
	"quality_5_button",
	"quality_4_button",
	"quality_3_button",
	"quality_2_button",
	"quality_1_button",
	NULL
};

static const short print_quality_button_value[] =
{
	CND_QUALITY_ABSOLUTE_HS,
	CND_QUALITY_ABSOLUTE_NORMAL,
	CND_QUALITY_ABSOLUTE_MQ,
	CND_QUALITY_ABSOLUTE_HQ,
	CND_QUALITY_ABSOLUTE_SPECIAL
};

static const gchar* bin_method_button_name[] =
{
	"ht_dither_button",
	"ht_ed_button",
	NULL
};

static const short bin_method_button_value[] =
{
	CND_UIBIN_PATTERN,
	CND_UIBIN_ED
};

static const short bin_method_pattern_value[] =
{
	CND_UIBIN_PATTERN,
	CND_UIBIN_PATTERN_HS,
	CND_UIBIN_V_PATTERN,
	-1
};


UIQualityDialog* CreateQualityDialog(UIDialog* parent)
{
	GtkWidget* window;
	UIQualityDialog* dialog
		 = (UIQualityDialog*)CreateDialog(sizeof(UIQualityDialog), parent);

#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window = LookupWidget(NULL, "quality_dialog");
#else
	UI_DIALOG(dialog)->window = window = create_quality_dialog();
#endif

	dialog->print_quality = GetCurrentnValue(CNCL_PRINTQUALITY);
	dialog->bin_method = GetCurrentnValue(CNCL_DITHER_PAT);

	SetCallbackTableFunc(CNCL_MEDIATYPE, (void*)SetQualityCustomValue, dialog);


	gtk_widget_realize(window);

	UpdateQualityDialogWidgets(window, NULL);

	return dialog;
}

void ShowQualityDialog(UIQualityDialog* dialog)
{
	UpdateQualityDialogWidgets(UI_DIALOG(dialog)->window, NULL);

	/*	
	dialog->print_quality = GetCurrentnValue(CNCL_PRINTQUALITY);
	dialog->bin_method = GetCurrentnValue(CNCL_DITHER_PAT);
	*/
	ShowDialog((UIDialog*)dialog, "quality_dialog_ok_button");
}

void HideQualityDialog(UIQualityDialog* dialog, gboolean apply)
{
	if( !apply )
	{
		// Recover parameters.
		UpdateMenuLink(CNCL_PRINTQUALITY, dialog->print_quality);
		UpdateMenuLink(CNCL_DITHER_PAT, dialog->bin_method);
	}
	else
		SetQualityCustomValue(dialog);
	

	HideDialog((UIDialog*)dialog);
}

gboolean
on_quality_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideQualityDialog(g_quality_dialog, FALSE);
	return TRUE;
}


void
on_quality_dialog_ok_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	HideQualityDialog(g_quality_dialog, TRUE);
}


void
on_quality_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	HideQualityDialog(g_quality_dialog, FALSE);
}


void
on_quality_dialog_help_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_quality_dialog_quality_i_button_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));
		int quality = GetActiveButtonIndex(window, print_quality_button_name,0);

		// Save the halftoning value before updating the print quality.
		short bin_method_value = GetCurrentnValue(CNCL_DITHER_PAT);
		short flag;

		UpdateMenuLink(CNCL_PRINTQUALITY, print_quality_button_value[quality]);

		// If can be set previous halftoning value, set it.
		flag = GetAllFlags(CNCL_DITHER_PAT, bin_method_value);
		if( !(flag & DISABLE_FLAG) )
			UpdateMenuLink(CNCL_DITHER_PAT, bin_method_value);

		UpdateQualityDialogWidgets(window, "quality_i_button");
	}
	EnableSignal();
}

void
on_quality_dialog_ht_button_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));
		int bin_method = GetActiveButtonIndex(window, bin_method_button_name,0);

		UpdateMenuLink(CNCL_DITHER_PAT, bin_method_button_value[bin_method]);

		UpdateQualityDialogWidgets(window, "quality_ht_button");
	}
	EnableSignal();
}

void UpdateQualityDialogWidgets(GtkWidget* window, gchar* except_name)
{
	// Print quality 1-5 button.
	int quality;

	for( quality = 0 ; print_quality_button_name[quality] != NULL ; quality++ )
	{
		GtkWidget* button
			 = LookupWidget(window, print_quality_button_name[quality]);
		short flag
			 = GetAllFlags(CNCL_PRINTQUALITY,
				 print_quality_button_value[quality]);

		if( flag & DISABLE_FLAG )
			gtk_widget_set_sensitive(button, FALSE);
		else
			gtk_widget_set_sensitive(button, TRUE);

		if( flag & CURRENT_FLAG )
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
		}
	}

	{
		short quality_value = GetCurrentnValue(CNCL_PRINTQUALITY);
		GtkWidget* button;
		short value[3];
		int i;

		for( i = 0 ; i < 3 ; i++ )
		{
			button = LookupWidget(UI_DIALOG(g_main_window)->window,
								g_quality_button_name[i]);
			value[i] = GetCurrentnValue(g_mess_map[i]);

			if( value[i] == quality_value )
			{
				gtk_label_set_text(
					GTK_LABEL(LookupWidget(window, "quality_level_name_label")),
						GTK_LABEL(GTK_BIN(button)->child)->label);
				break;
			}
		}
		if( i == 3 )
		{
				gtk_label_set_text(
					GTK_LABEL(LookupWidget(window, "quality_level_name_label")),"");
		}

		{	/* Ver.2.70: Write 5position value always */
			int index
			 	= GetActiveButtonIndex( window, print_quality_button_name, 0);
			char message[16];

			sprintf(message, "%d", 5 - index);
			gtk_label_set_text(
				GTK_LABEL(
					LookupWidget(window, "quality_level_num_label")), message);
		}
	}

	// Halftoning button and label.
	{
		int bin_method;
		for( bin_method = 0
			; bin_method_button_name[bin_method] != NULL ; bin_method++ )
		{
			GtkWidget* button
				 = LookupWidget(window, bin_method_button_name[bin_method]);
			gboolean sensitive;
			gboolean toggle;

			if( bin_method_button_value[bin_method] == CND_UIBIN_PATTERN )
			{
				short flag0 = 0;
				short flag1 = -1;
				int i;

				for( i = 0 ; bin_method_pattern_value[i] != -1 ; i++ )
				{
					short flag = GetAllFlags(CNCL_DITHER_PAT,
								 bin_method_pattern_value[i]);
					if( flag != -1 )
					{
						flag1 &= flag;
						flag0 |= flag;
					}
				}

				sensitive = (flag1 & DISABLE_FLAG)? FALSE :TRUE;
				toggle    = (flag0 & CURRENT_FLAG)? TRUE : FALSE;
			}
			else
			{
				short flag = GetAllFlags(CNCL_DITHER_PAT, CND_UIBIN_ED);

				sensitive = (flag & DISABLE_FLAG)? FALSE : TRUE;
				toggle    = (flag & CURRENT_FLAG)? TRUE : FALSE;
			}

			gtk_widget_set_sensitive(button, sensitive);
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), toggle);
		}
	}
}

void SetQualityCustomValue(void* param)
{
	UIQualityDialog* dialog = (UIQualityDialog*)param;

	dialog->print_quality = GetCurrentnValue(CNCL_PRINTQUALITY);
	dialog->bin_method = GetCurrentnValue(CNCL_DITHER_PAT);
}
