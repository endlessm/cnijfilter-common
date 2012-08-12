/*  Canon Bubble Jet Print Filter.
 *  Copyright CANON INC. 2001-2003
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

#include <string.h>

#include "bjuidefs.h"


#define	CYAN_BALANCE_INIT		0
#define	MAGENTA_BALANCE_INIT	0
#define	YELLOW_BALANCE_INIT		0
#define	BLACK_BALANCE_INIT		0
#define	DENSITY_BALANCE_INIT	0


#define	COLOR_CORRECT_INIT		CND_INTENT_PHOTO
#define	INPUT_GAMMA_INIT		CND_GAMMA_18
#define	VIVID_INIT				FALSE

static const gchar* correct_key[] =
{
	"color_correct_photo",
	"color_correct_graphics",
	NULL
};

static const short correct_value[] =
{
	CND_INTENT_PHOTO,
	CND_INTENT_GRAPHICS
};

const gchar* gamma_key[] =
{
	"input_gamma_1.4",
	"input_gamma_1.8",
	"input_gamma_2.2",
	NULL
};

static const short gamma_value[] =
{
	CND_GAMMA_14,
	CND_GAMMA_18,
	CND_GAMMA_22,
};


static const char* bw_sensitive_name[] =
{
	"color_dialog_balance_label",
	"color_dialog_cyan_label",
	"color_dialog_magenta_label",
	"color_dialog_yellow_label",
	"color_dialog_black_label",
	"color_dialog_correct_label",
	"color_dialog_gamma_label",

	"color_dialog_cyan_value",
	"color_dialog_magenta_value",
	"color_dialog_yellow_value",
	"color_dialog_black_value",

	"color_dialog_cyan_scale",
	"color_dialog_magenta_scale",
	"color_dialog_yellow_scale",
	"color_dialog_black_scale",

	"color_dialog_cyan_pixmap",
	"color_dialog_magenta_pixmap",
	"color_dialog_yellow_pixmap",
	"color_dialog_black_pixmap",

	"color_dialog_vivid_button",
	"color_dialog_correct_combo",
	"color_dialog_gamma_combo",
	NULL,
};

static short GetDefaultGamma(UIColorDialog* dialog)
{
	short gamma = GetDefaultnValue(CNCL_INPUT_GAMMA);

	if( gamma == -1 )
		gamma = INPUT_GAMMA_INIT;

	return gamma;
}

static short SetColorCorrectCombo(UIColorDialog* dialog, short color_correct)
{
	SetTextArrayToCombo(UI_DIALOG(dialog)->window,
		"color_dialog_correct_combo",
			 correct_key, correct_value, color_correct);

	return color_correct;
}

static short GetColorCorrectCombo(UIColorDialog* dialog)
{
	 return GetTextArrayValueFromCombo(UI_DIALOG(dialog)->window,
			 "color_dialog_correct_combo", correct_key, correct_value);
}

static void SensitiveColorCorrectCombo(
					UIColorDialog* dialog, gboolean sensitive) 
{
	GtkWidget* combo
		= LookupWidget(UI_DIALOG(dialog)->window, "color_dialog_correct_combo");

	gtk_widget_set_sensitive(combo, sensitive);
}

static short SetGammaCombo(UIColorDialog* dialog, short gamma)
{
	dialog->gamma_list = GetComboList(CNCL_INPUT_GAMMA);

	if( dialog->gamma_list )
	{
		gchar* name;

		if( gamma != GetCurrentnValue(CNCL_INPUT_GAMMA) )
			UpdateMenuLink(CNCL_INPUT_GAMMA, gamma);

		name = ValueToName(CNCL_INPUT_GAMMA, gamma);

		SetGListToCombo(UI_DIALOG(dialog)->window,
			"color_dialog_gamma_combo", dialog->gamma_list, name);
	}
	else
	{
		SetTextArrayToCombo(UI_DIALOG(dialog)->window,
			"color_dialog_gamma_combo", gamma_key, gamma_value, gamma);
	}

	return gamma;
}

UIColorDialog* CreateColorDialog(UIDialog* parent)
{
	GtkWidget* window;
	GtkAdjustment* adjust;
	// Create dialog.
	UIColorDialog* dialog
		 = (UIColorDialog*)CreateDialog(sizeof(UIColorDialog), parent);

	// Create dialog window.
#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = window = LookupWidget(NULL, "color_dialog");
#else
	UI_DIALOG(dialog)->window = window = create_color_dialog();
#endif

	// Cyan scale adjustment.
	adjust = gtk_range_get_adjustment(
		GTK_RANGE(LookupWidget(window, "color_dialog_cyan_scale")));
	gtk_signal_connect(GTK_OBJECT(adjust), "value_changed",
		GTK_SIGNAL_FUNC(on_color_dialog_cyan_adjust_value_changed), window);
	dialog->cyan_balance = CYAN_BALANCE_INIT;
	dialog->cyan_adjust = adjust;

	// Magenta scale adjustment.
	adjust = gtk_range_get_adjustment(
		GTK_RANGE(LookupWidget(window, "color_dialog_magenta_scale")));
	gtk_signal_connect(GTK_OBJECT(adjust), "value_changed",
		GTK_SIGNAL_FUNC(on_color_dialog_magenta_adjust_value_changed), window);
	dialog->magenta_balance = MAGENTA_BALANCE_INIT;
	dialog->magenta_adjust = adjust;

	// Yellow scale adjustment.
	adjust = gtk_range_get_adjustment(
		GTK_RANGE(LookupWidget(window, "color_dialog_yellow_scale")));
	gtk_signal_connect(GTK_OBJECT(adjust), "value_changed",
		GTK_SIGNAL_FUNC(on_color_dialog_yellow_adjust_value_changed), window);
	dialog->yellow_balance = YELLOW_BALANCE_INIT;
	dialog->yellow_adjust = adjust;

	// Black scale adjustment.
	adjust = gtk_range_get_adjustment(
			GTK_RANGE(LookupWidget(window, "color_dialog_black_scale")));
	gtk_signal_connect(GTK_OBJECT(adjust), "value_changed",
		GTK_SIGNAL_FUNC(on_color_dialog_black_adjust_value_changed), window);
	dialog->black_balance = BLACK_BALANCE_INIT;
	dialog->black_adjust = adjust;

	// Density scale adjustment.
	adjust = gtk_range_get_adjustment(
			GTK_RANGE(LookupWidget(window, "color_dialog_density_scale")));
	gtk_signal_connect(GTK_OBJECT(adjust), "value_changed",
		GTK_SIGNAL_FUNC(on_color_dialog_density_adjust_value_changed), window);
	dialog->density_balance = DENSITY_BALANCE_INIT;
	dialog->density_adjust = adjust;

	// Color correct combo.
	dialog->color_correct = SetColorCorrectCombo(dialog, COLOR_CORRECT_INIT);

	// Gamma combo.
	dialog->default_gamma =
	dialog->gamma = SetGammaCombo(dialog, GetDefaultGamma(dialog));

	dialog->vivid = FALSE;

	// Show vivid button if supported.
	if( IsAvailableVivid() )
	{
		gtk_widget_show(LookupWidget(window, "color_dialog_vivid_button"));
	}
	return dialog;
}

void ShowColorDialog(UIColorDialog* dialog)
{
	// Set cyan scale adjustment value.
	gtk_adjustment_set_value(dialog->cyan_adjust,
							(gfloat)dialog->cyan_balance);

	// Set magenta scale adjustment value.
	gtk_adjustment_set_value(dialog->magenta_adjust,
							(gfloat)dialog->magenta_balance);

	// Set yellow scale adjustment value.
	gtk_adjustment_set_value(dialog->yellow_adjust,
							(float)dialog->yellow_balance);

	// Set black scale adjustment value.
	gtk_adjustment_set_value(dialog->black_adjust,
							(float)dialog->black_balance);

	// Set density scale adjustment value.
	gtk_adjustment_set_value(dialog->density_adjust,
							(float)dialog->density_balance);

	// Vivid button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
		"color_dialog_vivid_button")), dialog->vivid);

	// Color correct combo.
	dialog->color_correct = SetColorCorrectCombo(dialog, dialog->color_correct);
	SensitiveColorCorrectCombo(dialog, !dialog->vivid); 

	// Gamma combo.
	dialog->gamma = SetGammaCombo(dialog, dialog->gamma);

	{
		short print_bw = IsGrayPrint(g_main_window);
		int i;

		for( i = 0 ; bw_sensitive_name[i] != NULL ; i++ )
		{
			gboolean sensitive;

			if( !strcmp(bw_sensitive_name[i], "color_dialog_correct_combo") )
				sensitive = !(print_bw | dialog->vivid);
			else
				sensitive = !print_bw;

			gtk_widget_set_sensitive(
				LookupWidget(UI_DIALOG(dialog)->window,
				 			bw_sensitive_name[i]), sensitive);
		}
	}

	ShowDialog((UIDialog*)dialog, "color_dialog_ok_button"); 
}

void HideColorDialog(UIColorDialog* dialog, gboolean apply)
{
	if( apply )
	{
		dialog->cyan_balance    = (int)dialog->cyan_adjust->value; 
		dialog->magenta_balance = (int)dialog->magenta_adjust->value; 
		dialog->yellow_balance  = (int)dialog->yellow_adjust->value; 
		dialog->black_balance   = (int)dialog->black_adjust->value; 
		dialog->density_balance = (int)dialog->density_adjust->value; 

		dialog->vivid
			= GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
					"color_dialog_vivid_button"))->active;

		dialog->color_correct = GetColorCorrectCombo(dialog);

		if( dialog->gamma_list == NULL )
		{
			dialog->gamma
				 = GetTextArrayValueFromCombo(UI_DIALOG(dialog)->window,
					 "color_dialog_gamma_combo", gamma_key, gamma_value);
		}
		else
		{
			dialog->gamma = GetCurrentnValue(CNCL_INPUT_GAMMA);
		}
	}
	else
	{
		if( dialog->gamma_list )
		{
			// Recover parameters.
			UpdateMenuLink(CNCL_INPUT_GAMMA, dialog->gamma);
		}
	}

	HideDialog((UIDialog*)dialog);
}

UIColorDialog* ReCreateColorDialog(UIColorDialog* dialog, UIDialog* parent)
{
	DisposeDialog((UIDialog*)dialog);
	return CreateColorDialog(parent);
}

void on_color_dialog_cyan_adjust_value_changed(
		GtkAdjustment* adjust, gpointer* user_data)
{
	UpdateScaleValue(GTK_WIDGET(user_data), adjust,
						 "color_dialog_cyan_value");
}

void on_color_dialog_magenta_adjust_value_changed(
		GtkAdjustment* adjust, gpointer* user_data)
{
	UpdateScaleValue(GTK_WIDGET(user_data), adjust,
						 "color_dialog_magenta_value");
}

void on_color_dialog_yellow_adjust_value_changed(
		GtkAdjustment* adjust, gpointer* user_data)

{
	UpdateScaleValue(GTK_WIDGET(user_data), adjust,
						 "color_dialog_yellow_value");
}

void on_color_dialog_black_adjust_value_changed(
		GtkAdjustment* adjust, gpointer* user_data)
{
	UpdateScaleValue(GTK_WIDGET(user_data), adjust,
						 "color_dialog_black_value");
}

void on_color_dialog_density_adjust_value_changed(
		GtkAdjustment* adjust, gpointer* user_data)
{
	UpdateScaleValue(GTK_WIDGET(user_data), adjust,
						 "color_dialog_density_value");
}

gboolean
on_color_dialog_delete_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideColorDialog(g_color_dialog, FALSE);
	return TRUE;
}

void
on_color_dialog_ok_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	HideColorDialog(g_color_dialog, TRUE);
}


void
on_color_dialog_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	HideColorDialog(g_color_dialog, FALSE);
}


void
on_color_dialog_default_button_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	UIColorDialog* dialog = g_color_dialog;
	short print_bw = IsGrayPrint(g_main_window);

	// Set cyan scale adjustment value.
	gtk_adjustment_set_value(dialog->cyan_adjust,
						(gfloat)CYAN_BALANCE_INIT);

	// Set magenta scale adjustment value.
	gtk_adjustment_set_value(dialog->magenta_adjust,
						(gfloat)MAGENTA_BALANCE_INIT);

	// Set yellow scale adjustment value.
	gtk_adjustment_set_value(dialog->yellow_adjust,
						(float)YELLOW_BALANCE_INIT);

	// Set black scale adjustment value.
	gtk_adjustment_set_value(dialog->black_adjust,
						(float)BLACK_BALANCE_INIT);

	// Set density scale adjustment value.
	gtk_adjustment_set_value(dialog->density_adjust,
						(float)DENSITY_BALANCE_INIT);

	// Vivid button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(dialog)->window,
			"color_dialog_vivid_button")), VIVID_INIT);

	// Color correct combo.
	SetColorCorrectCombo(dialog, COLOR_CORRECT_INIT);
	SensitiveColorCorrectCombo(dialog, !(VIVID_INIT | print_bw));

	// Gamma correct combo.
	SetGammaCombo(dialog, GetDefaultGamma(dialog));
}


void
on_color_dialog_gamma_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
	short gamma = NameToValue(CNCL_INPUT_GAMMA,
							(char*)gtk_entry_get_text(GTK_ENTRY(editable)));

	UpdateMenuLink(CNCL_INPUT_GAMMA, gamma);
}

void
on_color_dialog_help_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_color_dialog_vivid_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
	gboolean vivid_active = GTK_TOGGLE_BUTTON(LookupWidget(window,
								"color_dialog_vivid_button"))->active;

	SensitiveColorCorrectCombo(g_color_dialog, !vivid_active);
}

