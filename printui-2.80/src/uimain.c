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


#include "bjuidefs.h"


UIMainDialog* CreateMainWindow()
{
	short supply_value;
	short margin_value;
	UIMainDialog* main_window
		= (UIMainDialog*)CreateDialog(sizeof(UIMainDialog), NULL);

#ifdef	USE_LIB_GLADE
	UI_DIALOG(main_window)->window = LookupWidget(NULL, "ui_window");
#else
	UI_DIALOG(main_window)->window = create_ui_window();
#endif

	// Get initial paper size.
	main_window->init_paper_size = GetCurrentnValue(CNCL_PAPERSIZE);

	// Initialize auto color adjustment.
	main_window->color_auto = TRUE;

	// Initialize printing type, etc.
	main_window->printing_type = g_printing_type_value[0];
	main_window->scaling = 100;
	main_window->centering = LOCATION_UPPERLEFT;
	main_window->ext_border = GetDefaultExtBorder(g_model_id);
	main_window->stapleside = STAPLESIDE_LONG;
	main_window->copies = 1;

	// Save current supply & margin value .
	supply_value = GetCurrentnValue(CNCL_MEDIASUPPLY);
	margin_value = GetCurrentnValue(CNCL_MARGINTYPE);

	// Store ASF supply value.
	UpdateMenuLink(CNCL_MEDIASUPPLY, CND_SUPPLY_ASF);

	// Save list.
	g_paper_size_list = GetComboList(CNCL_PAPERSIZE);

	// Store ASF supply value.
	UpdateMenuLink(CNCL_MARGINTYPE, CND_MARGIN_MINUS);

	// Save list.
	g_paper_size_margin_list = GetComboList(CNCL_PAPERSIZE);

	// Store current supply value.
	UpdateMenuLink(CNCL_MARGINTYPE, margin_value);
	UpdateMenuLink(CNCL_MEDIASUPPLY, supply_value);

	return main_window;
}

void ConnectSignalHandlers()
{
	GtkWidget* combo;

	// Media type combo.
	combo = LookupWidget(UI_DIALOG(g_main_window)->window, "media_type_combo");
	gtk_widget_realize(combo);

	// Media size combo.
	combo = LookupWidget(UI_DIALOG(g_main_window)->window, "media_size_combo");
	gtk_widget_realize(combo);

	// Media supply combo.
	combo = LookupWidget(
				UI_DIALOG(g_main_window)->window, "media_supply_combo");
	gtk_widget_realize(combo);

	// Cartridge type combo.
	combo = LookupWidget(
				UI_DIALOG(g_main_window)->window, "cartridge_type_combo");
	gtk_widget_realize(combo);

	// Printing type combo.
	combo = LookupWidget(
				UI_DIALOG(g_main_window)->window, "printing_type_combo");
	gtk_widget_realize(combo);
}

void InitPrintingType()
{
	int i;
	const gchar** type_name;
	const short* type_value;

	if( g_cups_mode == FALSE )
	{
		type_name = g_printing_type_norm_name;
		type_value = g_printing_type_norm_value;
	}
	else
	{
		type_name = g_printing_type_cups_name;
		type_value = g_printing_type_cups_value;
	}

	for( i = 0 ; ; i++, type_name++, type_value++ )
	{
		g_printing_type_name[i] = (gchar*)(*type_name);
		g_printing_type_value[i] = (short)(*type_value);

		if( *type_name == NULL )
			break;
	}
}

static
void ShowCartridgeVBox(UIMainDialog* main_window)
{
	// Show or hide cartridge combo and label.
	if( GetComboNum(CNCL_CARTRIDGE) > 1 )
	{
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"cartridge_type_vbox"));
	}
	else
	{
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"one_cartridge_vbox"));
	}
}

static
void ShowBorderlessVBox(UIMainDialog* main_window)
{
	if( IsAvailableBorderless() && g_cups_mode == FALSE )
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"borderless_vbox"));
}

static
void ShowDuplexVBox(UIMainDialog* main_window)
{
	if( IsAvailableDuplex() )
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"duplex_printing_vbox"));
}

static
void ShowUtilButton(UIMainDialog* main_window, char* button_name)
{
	GtkWidget* button
		= LookupWidget(UI_DIALOG(main_window)->window, button_name);
	gtk_widget_show(button);

/*
	if( g_cups_mode == FALSE )
	{
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"monitor_button"));
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"monitor_hseparator"));
	}
*/
}

static
void ShowUtilButtons(UIMainDialog* main_window)
{
	short util_flag = GetUtilFlag(g_model_id);

	if( util_flag & UF_CLEANING )
		ShowUtilButton(main_window, "util_clean_button");
	if( util_flag & UF_DEEP_CLEANING )
		ShowUtilButton(main_window, "util_refresh_button");
	if( util_flag & UF_PLATE_CLEANING )
		ShowUtilButton(main_window, "util_plate_clean_button");
	if( util_flag & UF_ROLLER_CLEANING )
		ShowUtilButton(main_window, "util_roller_clean_button");
	if( util_flag & UF_NOZZLE_CHECK )
		ShowUtilButton(main_window, "util_nozzle_check_button");
	if( util_flag & UF_HEAD_ALIGNMENT )
		ShowUtilButton(main_window, "util_head_adjust_button");
	if( util_flag & UF_INK_RESET )
		ShowUtilButton(main_window, "util_ink_reset_button");
	if( util_flag & UF_INK_WARNING ){
		// init settings
		init_inkwarning_settings();
		ShowUtilButton(main_window, "util_ink_warning_button");
	}
	if( util_flag & UF_POWER_OFF )
		ShowUtilButton(main_window, "util_power_off_button");
	if( util_flag & UF_AUTO_POWER ){
		// init settings
		init_autopower_settings();
		init_autopower_type2_settings();
		ShowUtilButton(main_window, "util_auto_power_button");
	}
	if( util_flag & UF_CUSTOM ){
		// init settings
		init_papergap_settings();
		init_manual_head_settings();
		init_drylevel_value();
		ShowUtilButton(main_window, "util_config_button");
	}
	if( util_flag & UF_QUIET ){
		// init settings
		init_quiet_settings();
		ShowUtilButton(main_window, "util_quiet_button");
	}
	if( util_flag & UF_INK_CARTRIDGE )
		ShowUtilButton(main_window, "util_ink_cartridge_button");
}

static
void ShowPaperGapCombo(main_window)
{
	int show_lever_box = FALSE;

	/* Ver.2.80: Set "lever_label" string according to model_name. */
	GtkWidget* label = LookupWidget( UI_DIALOG(main_window)->window, "lever_label");
	gchar* label_name = ValueToName( CNUI_OBJECT_LEVER , CNUI_VALUE_LEVER_LABEL );
	gtk_label_set_text(GTK_LABEL(label), label_name);

	
	if( GetCurrentPaperGap() == CND_PGAP_CMD_NA )
	{
		if( GetCurrentnValue(CNCL_MESS_THICK) != CND_TMESSAGE_NA )
		{
			gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
				"lever_pos_hbox"));
			show_lever_box = TRUE;
		}
	}
	else
	{
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"paper_gap_hbox"));
		show_lever_box = TRUE;
	}

	if( show_lever_box == TRUE )
	{
		gtk_widget_show(LookupWidget(UI_DIALOG(main_window)->window,
			"lever_pos_vbox"));
	}
}

void ShowModelDependWidgets(UIMainDialog* main_window)
{
	// Show cartridge type box.
	ShowCartridgeVBox(main_window);

	// Show Borderless widgets.
	ShowBorderlessVBox(main_window);

	// Show Duplex widgets.
	ShowDuplexVBox(main_window);

	// Show utility buttons.
	ShowUtilButtons(main_window);

	// Show paper gap combo.
	ShowPaperGapCombo(main_window);
}

gboolean IsGrayPrint(UIMainDialog* main_window)
{
	GtkWidget* window = UI_DIALOG(main_window)->window;
	GtkWidget* bw_button1 = LookupWidget(window, "print_bw_button1");
	GtkWidget* bw_button2 = LookupWidget(window, "print_bw_button2");

	gboolean enable_bw
		 = ((GTK_WIDGET_IS_SENSITIVE(bw_button1))?
			GTK_TOGGLE_BUTTON(bw_button1)->active : TRUE)
		 || GTK_TOGGLE_BUTTON(bw_button2)->active;

	return enable_bw;
}

