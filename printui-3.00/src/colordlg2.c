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
#include <string.h>
#include <stdlib.h>

#include "bjuidefs.h"


#define	CYAN_BALANCE_INIT		0
#define	MAGENTA_BALANCE_INIT	0
#define	YELLOW_BALANCE_INIT		0
#define	CONTRAST_BALANCE_INIT	0
#define	DENSITY_BALANCE_INIT	0

#define	VIVID_INIT				FALSE


/* Ver.2.90 */
#define	CYAN_DLG_ID			0
#define	MAGENTA_DLG_ID		1
#define	YELLOW_DLG_ID		2
#define	DENSITY_DLG_ID		3
#define	CONTRAST_DLG_ID		4

typedef struct {
	const gchar* scale_name;
	const gchar* spin_name;
} SpinScaleTable;

static const SpinScaleTable spin_scale_table[] =
{
	{ "color_dialog_cyan_scale2", "c_dlg_c_value_spin2"},
	{ "color_dialog_magenta_scale2", "c_dlg_m_value_spin2"},
	{ "color_dialog_yellow_scale2", "c_dlg_y_value_spin2"},
	{ "color_dialog_density_scale2", "c_dlg_density_value_spin2"},
	{ "color_dialog_contrast_scale2", "c_dlg_contrast_value_spin2"},
};


static const char* bw_sensitive_name[] =
{
	"color_dialog_vivid_button2",
	"color_dialog_correct_label2",
	"color_dialog_correct_combo2",

	"color_dialog_balance_label2",

	"color_dialog_cyan_label2",
	"color_dialog_magenta_label2",
	"color_dialog_yellow_label2",

	"color_dialog_cyan_scale2",
	"color_dialog_magenta_scale2",
	"color_dialog_yellow_scale2",

	/* Ver.2.90 */
	"c_dlg_c_value_spin2",
	"c_dlg_m_value_spin2",
	"c_dlg_y_value_spin2",
	"c_dlg_c_low_xpm2",
	"c_dlg_c_high_xpm2",
	"c_dlg_m_low_xpm2",
	"c_dlg_m_high_xpm2",
	"c_dlg_y_low_xpm2",
	"c_dlg_y_high_xpm2",

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

/* Ver.2.90 */
static short CofirmSpinValue( spinbutton )
{
	short	result = 0;

	if( !strncmp( gtk_entry_get_text( GTK_ENTRY( spinbutton ) ), "-0" , 2 ) )
	{
		//gtk_entry_set_text( GTK_ENTRY( spinbutton ) , "0" );
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton), 1 );
		gtk_spin_button_set_value( GTK_SPIN_BUTTON( spinbutton), 0 );
		
		result = 1;
	}
		
	return result;
}


/*--------------------------------------*/
/* Create                               */
/*--------------------------------------*/
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


UIColorDialog2* ReCreateColorDialog2(UIColorDialog2* dialog, UIDialog* parent)
{
	DisposeDialog((UIDialog*)dialog);
	return CreateColorDialog2(parent);
}


/*--------------------------------------*/
/* Show                                 */
/*--------------------------------------*/
void ShowColorDialog2(UIColorDialog2* dialog)
{
	/* Ver.2.80 */
	DisableSignal();

	GtkWidget* window = UI_DIALOG(dialog)->window;

	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_cyan_scale2")) , (gdouble)dialog->cyan_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_magenta_scale2")) , (gdouble)dialog->magenta_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_yellow_scale2")) , (gdouble)dialog->yellow_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_density_scale2")) ,(gdouble)dialog->density_balance );
	gtk_range_set_value( GTK_RANGE(LookupWidget(window, "color_dialog_contrast_scale2")) , (gdouble)dialog->contrast_balance );

	/* Ver.2.90 */
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_c_value_spin2")) , (gdouble)dialog->cyan_balance );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_m_value_spin2")) , (gdouble)dialog->magenta_balance );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_y_value_spin2")) , (gdouble)dialog->yellow_balance );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_density_value_spin2")) , (gdouble)dialog->density_balance );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_contrast_value_spin2")) , (gdouble)dialog->contrast_balance );

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


/*--------------------------------------*/
/* OK or Cancel Button (close dialog)   */
/*--------------------------------------*/
void HideColorDialog2(UIColorDialog2* dialog, gboolean apply)
{
	/* Ver.2.80 */
	GtkWidget* window = UI_DIALOG(dialog)->window;

	if( apply )
	{
		/* Ver.2.90 */
		dialog->cyan_balance = (short)atoi( gtk_entry_get_text( GTK_ENTRY( LookupWidget( window , "c_dlg_c_value_spin2") ) ) );
		dialog->magenta_balance = (short)atoi( gtk_entry_get_text( GTK_ENTRY( LookupWidget( window , "c_dlg_m_value_spin2") ) ) );
		dialog->yellow_balance = (short)atoi( gtk_entry_get_text( GTK_ENTRY( LookupWidget( window , "c_dlg_y_value_spin2") ) ) );
		dialog->density_balance = (short)atoi( gtk_entry_get_text( GTK_ENTRY( LookupWidget( window , "c_dlg_density_value_spin2") ) ) );
		dialog->contrast_balance = (short)atoi( gtk_entry_get_text( GTK_ENTRY( LookupWidget( window , "c_dlg_contrast_value_spin2") ) ) );


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


/*--------------------------------------*/
/* Default Button                       */
/*--------------------------------------*/
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

	/* Ver.2.90 */
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_c_value_spin2")) , (gdouble)CYAN_BALANCE_INIT );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_m_value_spin2")) , (gdouble)MAGENTA_BALANCE_INIT );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_y_value_spin2")) , (gdouble)YELLOW_BALANCE_INIT );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_density_value_spin2")) , (gdouble)CONTRAST_BALANCE_INIT );
	gtk_spin_button_set_value( GTK_SPIN_BUTTON(LookupWidget(window, "c_dlg_contrast_value_spin2")) , (gdouble)DENSITY_BALANCE_INIT );


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


/*--------------------------------------*/
/* Help                                 */
/*--------------------------------------*/
void
on_color_dialog_help_button_clicked2    (GtkButton       *button,
                                        gpointer         user_data)
{

}

/*--------------------------------------*/
/* Vivid                                */
/*--------------------------------------*/
void
on_color_dialog_vivid_button_clicked2  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
	gboolean vivid_active = GTK_TOGGLE_BUTTON(LookupWidget(window,
								"color_dialog_vivid_button2"))->active;

	SensitiveColorCorrectCombo(g_color_dialog2, !vivid_active);
}


/*--------------------------------------*/
/* Spin Buttons and Scales (Ver.2.90)   */
/*--------------------------------------*/
/* Scale */
static void C_DLG_ScaleValueChanged( GtkRange   *range , short id )
{
	/* Ver.2.80 : Get the value from GtkRange (directly) */
	GtkWidget* window = UI_DIALOG(g_color_dialog2)->window;
	GtkSpinButton   *spinbutton = GTK_SPIN_BUTTON(LookupWidget( window, spin_scale_table[id].spin_name ) );

	
	if( DisableSignal() )	/* Ver.2.90: Prevent the endless loop between "scale" and "spinbutton" */
	{
		gtk_spin_button_set_value( spinbutton , (gdouble)gtk_range_get_value( range ) );

		/* Prevent from showing "-0" */
		if( CofirmSpinValue( spinbutton ) )
		{
#ifdef _PRINTUI_DEBUG_
			fprintf(stderr,"change -0 to 0 (C_DLG_ScaleValueChanged)\n" );
#endif
		}

	}
	EnableSignal();
}


void
on_color_dialog_cyan_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	C_DLG_ScaleValueChanged( range , CYAN_DLG_ID );
}


void
on_color_dialog_magenta_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	C_DLG_ScaleValueChanged( range , MAGENTA_DLG_ID );
}


void
on_color_dialog_yellow_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	C_DLG_ScaleValueChanged( range , YELLOW_DLG_ID );
}



void
on_color_dialog_density_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	C_DLG_ScaleValueChanged( range , DENSITY_DLG_ID );
}


void
on_color_dialog_contrast_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data)
{
	C_DLG_ScaleValueChanged( range , CONTRAST_DLG_ID );
}



/* Spin BUtton */
static void C_DLG_SpinValueChanged( GtkSpinButton   *spinbutton , short id )
{
	short	spin_value;
	GtkWidget* window = GetTopWidget(GTK_WIDGET(spinbutton));


	if( DisableSignal() )
	{
		spin_value = spinbutton->adjustment->value;
	
		/* Prevent from showing "-0" */
		if( CofirmSpinValue( spinbutton ) )
		{
#ifdef _PRINTUI_DEBUG_
			fprintf(stderr,"change -0 to 0 (C_DLG_SpinValueChanged)\n" );
#endif
		}

		/* Update sacle value */
		gtk_range_set_value( GTK_RANGE(LookupWidget(window, spin_scale_table[id].scale_name )) , (gdouble)spin_value );
	}
	EnableSignal();
}


void
on_c_dlg_c_value_spin2_value_changed   (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	C_DLG_SpinValueChanged( spinbutton , CYAN_DLG_ID );
}


void
on_c_dlg_m_value_spin2_value_changed   (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	C_DLG_SpinValueChanged( spinbutton , MAGENTA_DLG_ID );
}


void
on_c_dlg_y_value_spin2_value_changed   (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	C_DLG_SpinValueChanged( spinbutton , YELLOW_DLG_ID );
}


void
on_c_dlg_density_value_spin2_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	C_DLG_SpinValueChanged( spinbutton , DENSITY_DLG_ID );
}

void
on_c_dlg_contrast_value_spin2_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data)
{
	C_DLG_SpinValueChanged( spinbutton , CONTRAST_DLG_ID );
}


