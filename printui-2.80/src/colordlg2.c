/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2007
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#include <string.h>

#include "bjuidefs.h"


#define	CYAN_BALANCE_INIT		0
#define	MAGENTA_BALANCE_INIT	0
#define	YELLOW_BALANCE_INIT		0
#define	CONTRAST_BALANCE_INIT	0
#define	DENSITY_BALANCE_INIT	0

#define	VIVID_INIT				FALSE



static const char* bw_sensitive_name[] =
{
	"color_dialog_vivid_button2",
	"color_dialog_correct_label2",
	"color_dialog_correct_combo2",

	"color_dialog_balance_label2",

	"color_dialog_cyan_label2",
	"color_dialog_magenta_label2",
	"color_dialog_yellow_label2",

	"color_dialog_cyan_value2",
	"color_dialog_magenta_value2",
	"color_dialog_yellow_value2",

	"color_dialog_cyan_scale2",
	"color_dialog_magenta_scale2",
	"color_dialog_yellow_scale2",

	"color_dialog_cyan_pixmap2",
	"color_dialog_magenta_pixmap2",
	"color_dialog_yellow_pixmap2",

	"color_dialog_cyan_low2",
	"color_dialog_cyan_high2",
	"color_dialog_magenta_low2",
	"color_dialog_magenta_high2",
	"color_dialog_yellow_low2",
	"color_dialog_yellow_high2",
/* gamma , density , contrast : always sensitive */
	NULL,
};


/* for CND_FORMATTYPE_6 or above */
static short SetColorCorrectCombo2(UIColorDialog2* dialog , short intent)
{
	if( intent != GetCurrentnValue(CNCL_INTENT) )
		UpdateMenuLink(CNCL_INTENT, intent);

	/* Ver.2.80 */
	dialog->intent_num = SetItemsToComboBox( UI_DIALOG(dialog)->window, "color_dialog_correct_combo2", CNCL_INTENT, intent );
	
	return intent;
}


static void SensitiveColorCorrectCombo(
					UIColorDialog2* dialog, gboolean sensitive) 
{
	GtkWidget* combo
		= LookupWidget(UI_DIALOG(dialog)->window, "color_dialog_correct_combo2");

	gtk_widget_set_sensitive(combo, sensitive);
}


static short SetGammaCombo(UIColorDialog2* dialog, short gamma)
{
	if( gamma != GetCurrentnValue(CNCL_INPUT_GAMMA) )
		UpdateMenuLink(CNCL_INPUT_GAMMA, gamma);

	/* Ver.2.80 */
	SetItemsToComboBox( UI_DIALOG(dialog)->window, "color_dialog_gamma_combo2", CNCL_INPUT_GAMMA, gamma );

	return gamma;
}

UIColorDialog2* CreateColorDialog2(UIDialog* parent)
{
	GtkWidget* window;

	// Create dialog.
	UIColorDialog2* dialog
		 = (UIColorDialog2*)CreateDialog(sizeof(UIColorDialog2), parent);

	// Create dialog window.
#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window = LookupWidget(NULL, "color_dialog2");
#else
	UI_DIALOG(dialog)->window = window = create_color_dialog2();
#endif

	// Cyan scale adjustment.
	dialog->cyan_balance = CYAN_BALANCE_INIT;

	// Magenta scale adjustment.
	dialog->magenta_balance = MAGENTA_BALANCE_INIT;

	// Yellow scale adjustment.
	dialog->yellow_balance = YELLOW_BALANCE_INIT;

	// Contrast scale adjustment.
	dialog->contrast_balance = CONTRAST_BALANCE_INIT;

	// Density scale adjustment.
	dialog->density_balance = DENSITY_BALANCE_INIT;

	// Color correct combo.
	dialog->default_intent =
	dialog->color_correct = SetColorCorrectCombo2(dialog, GetDefaultnValue(CNCL_INTENT));

	// Gamma combo.
	dialog->default_gamma =
	dialog->gamma = SetGammaCombo(dialog, GetDefaultnValue(CNCL_INPUT_GAMMA));

	dialog->vivid = FALSE;

	// Show vivid button if supported.
	if( IsAvailableVivid() )
	{
		gtk_widget_show(LookupWidget(window, "color_dialog_vivid_button2"));
	}
	return dialog;
}

void ShowColorDialog2(UIColorDialog2* dialog)
{
	/* Ver.2.80 */
	DisableSignal();

	GtkWidget* window = UI_DIALOG(dialog)->window;

	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_cyan_scale2")) , (gdouble)dialog->cyan_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_magenta_scale2")) , (gdouble)dialog->magenta_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_yellow_scale2")) , (gdouble)dialog->yellow_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_contrast_scale2")) , (gdouble)dialog->contrast_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_density_scale2")) ,(gdouble)dialog->density_balance );


	// Vivid button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
		"color_dialog_vivid_button2")), dialog->vivid);

	// Gamma combo.
	dialog->gamma = SetGammaCombo(dialog, dialog->gamma);

	// Color correct combo.
	dialog->color_correct = SetColorCorrectCombo2(dialog, dialog->color_correct);
	SensitiveColorCorrectCombo(dialog, !dialog->vivid);

	{
		short print_bw = IsGrayPrint(g_main_window);
		int i;

		for( i = 0 ; bw_sensitive_name[i] != NULL ; i++ )
		{
			gboolean sensitive;

			if( !strcmp(bw_sensitive_name[i], "color_dialog_correct_combo2") )
				sensitive = !(print_bw | dialog->vivid);
			else
				sensitive = !print_bw;

			gtk_widget_set_sensitive(
				LookupWidget(UI_DIALOG(dialog)->window,
				 			bw_sensitive_name[i]), sensitive);
		}
	}

	/* If more than one intent exist , show "color_dialog_intent_table". */
	{
		GtkWidget* table = LookupWidget(UI_DIALOG(dialog)->window, "color_dialog_intent_table");

		/* Ver.280 */
		if( dialog->intent_num > 1 ) gtk_widget_show(table);
	}

	/* Ver.2.80 */
	EnableSignal();

	ShowDialog((UIDialog*)dialog, "color_dialog_ok_button2"); 
}


void HideColorDialog2(UIColorDialog2* dialog, gboolean apply)
{
	/* Ver.2.80 */
	GtkWidget* window = UI_DIALOG(dialog)->window;

	if( apply )
	{
		/* Ver.2.80 */
		dialog->cyan_balance    = (int)(gtk_range_get_value( GTK_RANGE(  LookupWidget( window , "color_dialog_cyan_scale2") ) ));
		dialog->magenta_balance = (int)(gtk_range_get_value( GTK_RANGE(  LookupWidget( window , "color_dialog_magenta_scale2") ) ));
		dialog->yellow_balance  = (int)(gtk_range_get_value( GTK_RANGE(  LookupWidget( window , "color_dialog_yellow_scale2") ) ));
		dialog->contrast_balance   = (int)(gtk_range_get_value( GTK_RANGE(  LookupWidget( window , "color_dialog_contrast_scale2") ) ));
		dialog->density_balance = (int)(gtk_range_get_value( GTK_RANGE(  LookupWidget( window , "color_dialog_density_scale2") ) ));


		dialog->vivid
			= GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
					"color_dialog_vivid_button2"))->active;

		/* CNCL_INTENT : Set current setting */
		dialog->color_correct = GetCurrentnValue(CNCL_INTENT);
		/* CNCL_INPUT_GAMMA : Set current setting */
		dialog->gamma = GetCurrentnValue(CNCL_INPUT_GAMMA);
	}
	else	
	{	/* "Cancel" -> Recover parameters. */
		UpdateMenuLink(CNCL_INPUT_GAMMA, dialog->gamma);
		UpdateMenuLink(CNCL_INTENT, dialog->color_correct);
	}

	HideDialog((UIDialog*)dialog);
}

UIColorDialog2* ReCreateColorDialog2(UIColorDialog2* dialog, UIDialog* parent)
{
	DisposeDialog((UIDialog*)dialog);
	return CreateColorDialog2(parent);
}



/* Ver.2.80 */
void
on_color_dialog_magenta_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	/* Ver.2.80 */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkWidget* label = LookupWidget(window, "color_dialog_magenta_value2" );
	gchar value[8];

	sprintf(value, "%3d", (int)(gtk_range_get_value( range )));
	gtk_label_set_text(GTK_LABEL(label), value );
}


void
on_color_dialog_yellow_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	/* Ver.2.80 : Get the value from GtkRange (directly) */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkWidget* label = LookupWidget(window, "color_dialog_yellow_value2" );
	gchar value[8];

	sprintf(value, "%3d", (int)(gtk_range_get_value( range )));
	gtk_label_set_text(GTK_LABEL(label), value );
}


void
on_color_dialog_cyan_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	/* Ver.2.80 : Get the value from GtkRange (directly) */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkWidget* label = LookupWidget(window, "color_dialog_cyan_value2" );
	gchar value[8];

	sprintf(value, "%3d", (int)(gtk_range_get_value( range )));
	gtk_label_set_text(GTK_LABEL(label), value );
}


void
on_color_dialog_density_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	/* Ver.2.80 : Get the value from GtkRange (directly) */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkWidget* label = LookupWidget(window, "color_dialog_density_value2" );
	gchar value[8];

	sprintf(value, "%3d", (int)(gtk_range_get_value( range )));
	gtk_label_set_text(GTK_LABEL(label), value );
}


void
on_color_dialog_contrast_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	/* Ver.2.80 : Get the value from GtkRange (directly) */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkWidget* label = LookupWidget(window, "color_dialog_contrast_value2" );
	gchar value[8];

	sprintf(value, "%3d", (int)(gtk_range_get_value( range )));
	gtk_label_set_text(GTK_LABEL(label), value );
}




gboolean
on_color_dialog_delete_event2          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideColorDialog2(g_color_dialog2, FALSE);
	return TRUE;
}

void
on_color_dialog_ok_button_clicked2     (GtkButton       *button,
                                        gpointer         user_data)
{
	HideColorDialog2(g_color_dialog2, TRUE);
}


void
on_color_dialog_cancel_button_clicked2 (GtkButton       *button,
                                        gpointer         user_data)
{
	HideColorDialog2(g_color_dialog2, FALSE);
}


void
on_color_dialog_default_button_clicked2 (GtkButton       *button,
                                        gpointer         user_data)
{
	UIColorDialog2* dialog = g_color_dialog2;
	short print_bw = IsGrayPrint(g_main_window);

	/* Ver.2.80 */
	GtkWidget* window = UI_DIALOG(dialog)->window;

	/* Ver.2.80 */
	DisableSignal();

	/* Ver.2.80 */
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_cyan_scale2")) , (gdouble)CYAN_BALANCE_INIT );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_magenta_scale2")) , (gdouble)MAGENTA_BALANCE_INIT );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_yellow_scale2")) , (gdouble)YELLOW_BALANCE_INIT );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_contrast_scale2")) , (gdouble)CONTRAST_BALANCE_INIT );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_density_scale2")) , (gdouble)DENSITY_BALANCE_INIT );


	// Vivid button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
			"color_dialog_vivid_button2")), VIVID_INIT);

	// Color correct combo.
	SetColorCorrectCombo2(dialog, GetDefaultnValue(CNCL_INTENT));
	SensitiveColorCorrectCombo(dialog, !(VIVID_INIT | print_bw));

	// Gamma correct combo.
	SetGammaCombo(dialog, GetDefaultnValue(CNCL_INPUT_GAMMA));

	/* Ver.2.80 */
	EnableSignal();
}



void
on_color_dialog_help_button_clicked2    (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_color_dialog_vivid_button_clicked2  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
	gboolean vivid_active = GTK_TOGGLE_BUTTON(LookupWidget(window,
								"color_dialog_vivid_button2"))->active;

	SensitiveColorCorrectCombo(g_color_dialog2, !vivid_active);
}

