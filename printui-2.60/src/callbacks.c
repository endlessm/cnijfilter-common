/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
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
#include <string.h>
#include <stdlib.h>

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"
#include "utility.h"


static void SetBJFltDevice(LPBJFLTDEVICE bjdev)
{
	memset(bjdev, 0, sizeof(BJFLTDEVICE));

	// Prepare for BJFLTDEVICE structure.
	bjdev->bjfltModelID      = g_uidb.ModelID;
	bjdev->bjfltMediaType    = GetCurrentnValue(CNCL_MEDIATYPE);
	bjdev->bjfltPrintQuality = GetCurrentnValue(CNCL_PRINTQUALITY);
	bjdev->bjfltMediaSupply  = GetCurrentnValue(CNCL_MEDIASUPPLY);
	bjdev->bjfltPaperSize    = GetCurrentnValue(CNCL_PAPERSIZE);
	bjdev->bjfltBinMethod    = GetCurrentnValue(CNCL_DITHER_PAT);

	if (bjdev->bjfltBinMethod == CND_UIBIN_PATTERN_HS)
		bjdev->bjfltBinMethod = CND_UIBIN_PATTERN;

	bjdev->bjfltBanner    = GetCurrentnValue(CNCL_BANNER);
	bjdev->bjfltInkType   = GetCurrentnValue(CNCL_CARTRIDGE);
	bjdev->bjfltGrayScale = GetCurrentnValue(CNCL_GRAYSCALE);

	bjdev->bjfltPaperWidth	= GetPaperWidth(bjdev->bjfltPaperSize);
	bjdev->bjfltPaperHeight	= GetPaperHeight(bjdev->bjfltPaperSize);

	if( IsAvailableBorderless() )
		bjdev->bjfltMarginType = GetCurrentnValue(CNCL_MARGINTYPE);
	else
		bjdev->bjfltMarginType = CND_MARGIN_NORMAL;

	bjdev->bjfltPaperGap = GetCurrentPaperGap();

	if( IsAvailableDuplex() && IsAvailableValue(CNCL_DUPLEX_PRINTING, CND_DUPLEX_AUTO) )
		bjdev->bjfltDuplex = GetCurrentnValue(CNCL_DUPLEX_PRINTING);
	else
		bjdev->bjfltDuplex = CND_DUPLEX_OFF;

	bjdev->bjfltInkcartridgesettings = GetCurrentInkCartridgeSettings();
}

static void SetBJFltColorSystem(LPBJFLTCOLORSYSTEM bjcolor)
{

	if( g_main_window->color_auto )
		g_color_dialog = 
			ReCreateColorDialog(g_color_dialog, UI_DIALOG(g_main_window));

	if( IsGrayPrint(g_main_window) )
	{
		bjcolor->bjfltIntent = CND_INTENT_PHOTO;

		bjcolor->bjfltGamma = g_color_dialog->default_gamma;
		bjcolor->bjfltBalanceC = 0;
		bjcolor->bjfltBalanceM = 0;
		bjcolor->bjfltBalanceY = 0;
		bjcolor->bjfltBalanceK = 0;
		bjcolor->bjfltDensity  = g_color_dialog->density_balance;
	}
	else
	{
		if( g_color_dialog->vivid )
			bjcolor->bjfltIntent = CND_INTENT_VIVID;
		else
			bjcolor->bjfltIntent = g_color_dialog->color_correct;

		bjcolor->bjfltGamma = g_color_dialog->gamma;
		bjcolor->bjfltBalanceC = g_color_dialog->cyan_balance;
		bjcolor->bjfltBalanceM = g_color_dialog->magenta_balance;
		bjcolor->bjfltBalanceY = g_color_dialog->yellow_balance;
		bjcolor->bjfltBalanceK = g_color_dialog->black_balance;
		bjcolor->bjfltDensity  = g_color_dialog->density_balance;
	}
}

static void SetUISetup(LPBJFLT_UISETUP uisetup)
{
	memset(uisetup, 0, sizeof(BJFLT_UISETUP));

	// Fit-page printing.
	if( g_main_window->printing_type == PRINTING_TYPE_FIT )
		uisetup->bjflt_fit = FIT_SHORT;
	else
		uisetup->bjflt_fit = FIT_OFF;

	// Scaling, etc.
	uisetup->bjflt_percent = g_main_window->scaling;
	uisetup->bjflt_location = g_main_window->centering;
	uisetup->bjflt_extension = g_main_window->ext_border;
	uisetup->bjflt_copies = g_main_window->copies;
	uisetup->bjflt_stapleside = g_main_window->stapleside;

	// Dummy.
	uisetup->bjflt_revprint = 0;
	uisetup->bjflt_collate = 0;
}

static void GetMargin(LPCNCLPAPERSIZE psize)
{
	short size = GetCurrentnValue(CNCL_PAPERSIZE);

	psize->nSelPaperWidth  = GetPaperWidth(size);
	psize->nSelPaperLength = GetPaperHeight(size);

	// Get paper margin.
	CNCL_GetMargin(&g_uidb.nominfo,
		(void*)g_bjlibdir, g_uidb.lpdbTop, psize, g_uidb.dbsize);
}

static void ShowLeverPositionAlert()
{
	gchar* position_alert_msg;
	gchar* msg_buf;
const static gchar* _alert_str = "_alert";

	gchar* alert_msg = LookupText(g_keytext_list, "move_lever_position_alert");
	gchar* position_key
			 = ValueToKey(CNCL_MESS_THICK, GetCurrentnValue(CNCL_MESS_THICK));

	// Make the key for the position string on the alert.
	gchar* position_alert_key
		 = g_malloc(strlen(position_key) + strlen(_alert_str) + 1);

	strcpy(position_alert_key, position_key);
	strcat(position_alert_key, _alert_str);

	// Get the position string on the alert.
	position_alert_msg = LookupText(g_keytext_list, position_alert_key);

	// If not exist, use the current position string instead.
	if( position_alert_msg == NULL )
		position_alert_msg = GetCurrentString(CNCL_MESS_THICK);

	msg_buf = (gchar*)g_malloc(strlen(alert_msg) + strlen(position_alert_msg));

	sprintf(msg_buf, alert_msg, position_alert_msg);

	UtilMessageBox(msg_buf, g_window_title, MB_OK | MB_ICON_INFORMATION);

	g_free(position_alert_key);
	g_free(msg_buf);
}

void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	BJFLTDEVICE bjdev;
	BJFLTCOLORSYSTEM bjcolor;
	BJFLT_UISETUP uisetup;
	CNCLPAPERSIZE psize;
	IPCU ipc;
	gboolean change_item;
	short thick_value;

	// Get paper margin.
	GetMargin(&psize);

	SetBJFltDevice(&bjdev);

	// Save the thickness value.
	thick_value = GetCurrentnValue(CNCL_MESS_THICK);

	// Check Media type and Media size combination.
	if( CheckMediaSizeCombination(&bjdev, &change_item) != TRUE )
		return;

	if( change_item )
	{
		// If change the thickness, show alert.
		if( thick_value != GetCurrentnValue(CNCL_MESS_THICK) )
			ShowLeverPositionAlert();

		// Get paper margin.
		GetMargin(&psize);

		SetBJFltDevice(&bjdev);
	}

	SetBJFltColorSystem(&bjcolor);

	// Make uisetup data.
	SetUISetup(&uisetup);

	// Then prepare for IPC

	memcpy(&ipc.parm.bjfltdev, &bjdev, sizeof(BJFLTDEVICE));
	memcpy(&ipc.parm.papersize, &psize, sizeof(CNCLPAPERSIZE));
	memcpy(&ipc.parm.bjfltcolor, &bjcolor, sizeof(BJFLTCOLORSYSTEM));
	memcpy(&ipc.parm.bjflt_uisetup, &uisetup, sizeof(BJFLT_UISETUP));

	if( g_socketname != NULL )
	{	// client mode

		PutIPCData(&ipc);
	}
	gtk_main_quit();
}

void
on_cancel_button_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	if( g_socketname != NULL )
	{
		PutCancel();
	}
	gtk_main_quit();
}


void
on_help_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
}

void
on_ui_window_destroy                   (GtkObject       *object,
                                        gpointer         user_data)
{
	on_cancel_button_clicked(NULL, NULL);
}

void
on_util_clean_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilCleaning(&g_uidb);
}

void
on_util_refresh_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilRefreshing(&g_uidb);
}

void
on_util_nozzle_check_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilNozzleCheck(&g_uidb);
}

void
on_util_head_adjust_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilHeadAdjust(&g_uidb);
}

void
on_util_roller_clean_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilRollerCleaning(&g_uidb);
}

void
on_util_plate_clean_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilPlateCleaning(&g_uidb);
}

void
on_util_power_off_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilPowerOff(&g_uidb);
}

void
on_util_auto_power_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilAutoPower(&g_uidb);
}

void
on_util_config_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilSetConfig(&g_uidb);
}

void
on_util_ink_reset_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilInkReset(&g_uidb);
}


void
on_util_ink_warning_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilInkWarning(&g_uidb);
}


void
on_util_quiet_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilQuietMode(&g_uidb);
}

void
on_monitor_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	PutExecLM();
}


#ifdef	GUI_WITH_PIXMAPS
gboolean
on_basic_draw_area_expose_event        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	DrawPrinterDrawingArea(GetTopWidget(widget), widget);
	return TRUE;
}
#endif


void
on_print_bw_button_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
		short value;

		if( IsGrayPrint(g_main_window) )
			value = CND_BJGRAYSCALE_ON;
		else
			value = CND_BJGRAYSCALE_OFF;

		UpdateMenuLink(CNCL_GRAYSCALE, value);

		UpdateWidgets(window, "print_bw_button");

#ifdef	GUI_WITH_PIXMAPS
		UpdateDrawingArea(window, "basic_draw_area");
		UpdateDrawingArea(window, "quality_draw_area");
#endif
	}
	EnableSignal();
}


gboolean
on_quality_draw_area_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	DrawQualityDrawingArea(GetTopWidget(widget), widget);
	return TRUE;
}

void
on_quality_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
		int quality
		 = g_mess_map[GetActiveButtonIndex(window, g_quality_button_name,0)];

		switch( quality )
		{
		case CNCL_MESS_Q_MAP1:
		case CNCL_MESS_Q_MAP2:
		case CNCL_MESS_Q_MAP3:
		{
			UpdateMenuLink(CNCL_PRINTQUALITY, GetCurrentnValue(quality));
			UpdateMenuLink(CNCL_DITHER_PAT, CND_UIBIN_ED);
			break;
		}
		default:
		{
			UpdateMenuLink(CNCL_PRINTQUALITY, g_quality_dialog->print_quality);
			UpdateMenuLink(CNCL_DITHER_PAT, g_quality_dialog->bin_method);
			break;
		}
		}
		

		UpdateWidgets(window, "quality_buttons");
#ifdef	GUI_WITH_PIXMAPS
		UpdateDrawingArea(window, "quality_draw_area");
#endif
	}
	EnableSignal();
}

static void
confirm_media_supply_change(short old_supply_value)
{
	int ret;
	gchar* alert_msg = LookupText(g_keytext_list, "paper_supply_change_alert");
	gchar* supply_str = GetCurrentString(CNCL_MEDIASUPPLY);
//	gchar* supply_str = ValueToName(CNCL_MEDIASUPPLY, old_supply_value);
	gchar* message = (gchar*)g_malloc(strlen(alert_msg) + strlen(supply_str));

	sprintf(message, alert_msg, supply_str);

	ret = UtilMessageBox(message, g_window_title,
			 MB_OK | MB_CANCEL | MB_ICON_INFORMATION);

	g_free(message);

	if( ret == ID_CANCEL )
	{
		UpdateMenuLink(CNCL_MEDIASUPPLY, old_supply_value);
	}
}

static void
update_by_media_type_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;
	GtkWidget* entry = LookupWidget(window, "media_type_entry");
	short type_value = NameToValue(CNCL_MEDIATYPE, 
				(char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	// Save current supply value.
	short supply_value = GetCurrentnValue(CNCL_MEDIASUPPLY);

	UpdateMenuLink(CNCL_MEDIATYPE, type_value);

	// If changed the supply value, show the alert.
//	if( supply_value != GetCurrentnValue(CNCL_MEDIASUPPLY) )
//	{
//		confirm_media_supply_change(supply_value);
//	}

	UpdateWidgets(window, "media_type_combo");
#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_media_type_entry_changed = FALSE;
}

gboolean
on_media_type_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_media_type_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_media_type_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			if( g_media_type_entry_changed )
			{
				update_by_media_type_entry();
			}
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_media_type_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_media_type_entry_changed = TRUE;

		if( !g_media_type_popwin_mapped )
		{
			update_by_media_type_entry();
		}
	}
	EnableSignal();
}

static void
set_user_paper_size()
{
	ShowUserSizeDialog(g_user_size_dialog);
}

static void
update_by_media_size_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;
	GtkWidget* entry = LookupWidget(window, "media_size_entry");
	short value = NameToValue(CNCL_PAPERSIZE, 
						(char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	if( !IsAvailablePageSize(g_pagesize_dialog,value) )
	{
		if( ShowPageSizeDialog(g_pagesize_dialog) )
		{
			// Change
			UpdateMenuLink(CNCL_MEDIASUPPLY, CND_SUPPLY_ASF);
			UpdateMenuLink(CNCL_PAPERSIZE, value);
			g_paper_size_value = value;

			if( CND_SIZE_USER == GetCurrentnValue(CNCL_PAPERSIZE) )
			{
				set_user_paper_size();
			}
		}
		else
		{
			// Back to Setup
			short margin_type = GetCurrentnValue(CNCL_MARGINTYPE);
			UpdateMenuLink(CNCL_PAPERSIZE, g_paper_size_value);
			if( margin_type == CND_MARGIN_MINUS )
			{
				SetGListToCombo(window, "media_size_combo",	g_paper_size_margin_list, 
								ValueToName(CNCL_PAPERSIZE,g_paper_size_value));
			}
			else
			{
				SetGListToCombo(window, "media_size_combo",	g_paper_size_list, 
								ValueToName(CNCL_PAPERSIZE,g_paper_size_value));
			}
		}
	}
	else
	{
		UpdateMenuLink(CNCL_PAPERSIZE, value);
		g_paper_size_value = value;

		if( CND_SIZE_USER == GetCurrentnValue(CNCL_PAPERSIZE) )
		{
			set_user_paper_size();
		}

	}

	UpdateWidgets(window,  "media_size_combo");
#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_media_size_entry_changed = FALSE;
}

gboolean
on_media_size_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_media_size_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_media_size_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			update_by_media_size_entry();
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_media_size_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_media_size_entry_changed = TRUE;

		if( !g_media_size_popwin_mapped )
		{
			update_by_media_size_entry();
		}
	}
	EnableSignal();
}

static void
update_by_media_supply_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;
	GtkWidget* entry = LookupWidget(window, "media_supply_entry");
	short value = NameToValue(CNCL_MEDIASUPPLY, 
						(char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	UpdateMenuLink(CNCL_MEDIASUPPLY, value);

	UpdateWidgets(window, "media_supply_combo");
#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_media_supply_entry_changed = FALSE;
}

gboolean
on_media_supply_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_media_supply_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_media_supply_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			if( g_media_supply_entry_changed )
			{
				update_by_media_supply_entry();
			}
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_media_supply_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_media_supply_entry_changed = TRUE;

		if( !g_media_supply_popwin_mapped )
		{
			update_by_media_supply_entry();
		}
	}
	EnableSignal();
}

static void
update_by_cartridge_type_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;
	GtkWidget* entry = LookupWidget(window, "cartridge_type_entry");
	short new_cartridge_value = NameToValue(CNCL_CARTRIDGE, 
						(char*)gtk_entry_get_text(GTK_ENTRY(entry)));
	short media_type_value = GetCurrentnValue(CNCL_MEDIATYPE);

	if( !IsAvailableMedia(g_mediatype_dialog,
			media_type_value, new_cartridge_value) )
	{
		short new_media_type_value;

		if( (new_media_type_value = ShowMediaTypeDialog(g_mediatype_dialog,
			media_type_value, new_cartridge_value)) != -1 )
		{
			UpdateMenuLink(CNCL_MEDIATYPE, new_media_type_value);
			UpdateMenuLink(CNCL_CARTRIDGE, new_cartridge_value);

#ifdef NEED_TO_SAVE_GRAYSCALE
			if( GetCurrentnValue(CNCL_GRAYSCALE) != CND_BJGRAYSCALE_GRAY )
			{
				short gray_scale_value = IsGrayPrint(g_main_window)?
						CND_BJGRAYSCALE_ON : CND_BJGRAYSCALE_OFF;

				UpdateMenuLink(CNCL_GRAYSCALE, gray_scale_value);
			}
#endif
			UpdateWidgets(window, "cartridge_type_combo");
		}
		else
		{
			UpdateWidgets(window, NULL);
		}
	}
	else
	{
		UpdateMenuLink(CNCL_CARTRIDGE, new_cartridge_value);

#ifdef NEED_TO_SAVE_GRAYSCALE
		if( GetCurrentnValue(CNCL_GRAYSCALE) != CND_BJGRAYSCALE_GRAY )
		{
			short gray_scale_value = IsGrayPrint(g_main_window)?
				CND_BJGRAYSCALE_ON : CND_BJGRAYSCALE_OFF;

			UpdateMenuLink(CNCL_GRAYSCALE, gray_scale_value);
		}
#endif
		UpdateWidgets(window, "cartridge_type_combo");
	}

#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_cartridge_type_entry_changed = FALSE;
}

gboolean
on_cartridge_type_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_cartridge_type_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_cartridge_type_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			if( g_cartridge_type_entry_changed )
			{
				update_by_cartridge_type_entry();
			}
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_cartridge_type_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_cartridge_type_entry_changed = TRUE;

		if( !g_cartridge_type_popwin_mapped )
		{
			update_by_cartridge_type_entry();
		}
	}
	EnableSignal();
}

void
on_color_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));
		GtkWidget* auto_button = LookupWidget(window, "color_auto_button");
		g_main_window->color_auto = GTK_TOGGLE_BUTTON(auto_button)->active;

		UpdateWidgets(GetTopWidget(GTK_WIDGET(button)), "color_buttons");
	}
	EnableSignal();
}

static void
update_by_paper_gap_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;
	GtkWidget* entry = LookupWidget(window, "paper_gap_entry");
	short value = NameToValue(CNCL_PAPERGAP_COMMAND, 
						(char*)gtk_entry_get_text(GTK_ENTRY(entry)));

	UpdateMenuLink(CNCL_PAPERGAP_COMMAND, value);
	UpdateWidgets(window, "paper_gap_combo");

#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_paper_gap_entry_changed = FALSE;
}

gboolean
on_paper_gap_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_paper_gap_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_paper_gap_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			if( g_paper_gap_entry_changed )
			{
				update_by_paper_gap_entry();
			}
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_paper_gap_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_paper_gap_entry_changed = TRUE;

		if( !g_paper_gap_popwin_mapped )
		{
			update_by_paper_gap_entry();
		}
	}
	EnableSignal();
}

void
on_version_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	ShowDialog((UIDialog*)g_version_dialog, "version_dlg_ok_button");
}

gboolean
on_version_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideDialog((UIDialog*)g_version_dialog);
	return TRUE;
}

void
on_version_dlg_ok_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	HideDialog((UIDialog*)g_version_dialog);
}

void
on_quality_dialog_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	ShowQualityDialog(g_quality_dialog);
}


void
on_color_dialog_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	ShowColorDialog(g_color_dialog);
}

#ifdef	GUI_WITH_PIXMAPS
gboolean
on_color_sample_draw_area_expose_event (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	GdkWindow* window = widget->window;
	GdkGC* gc = gdk_gc_new(window);
	GdkPixmap* pixmap;

	pixmap = LoadPixmap(GetTopWidget(widget), NULL, "color_sample.xpm");
	DrawPixmap(window, gc, 0, 0, pixmap, NULL);
	FreePixmap(pixmap, NULL);

	gdk_gc_unref(gc);
	return TRUE;
}
#endif

static void
update_by_printing_type_entry()
{
	GtkWidget* window = UI_DIALOG(g_main_window)->window;

	g_main_window->printing_type
		= GetTextArrayValueFromCombo(window, "printing_type_combo",
			(const gchar**)g_printing_type_name,
			(const short*)g_printing_type_value);

	if( g_main_window->printing_type != PRINTING_TYPE_SCALE )
		g_main_window->scaling = 100;

	UpdateWidgets(window, "printing_type_combo");

#ifdef	GUI_WITH_PIXMAPS
	UpdateDrawingArea(window, "basic_draw_area");
#endif
	g_printing_type_entry_changed = FALSE;
}

gboolean
on_printing_type_popwin_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_MAP )
	{
		g_printing_type_popwin_mapped = TRUE;
	}
	else if( event->type == GDK_UNMAP )
	{
		g_printing_type_popwin_mapped = FALSE;

		if( DisableSignal() )
		{
			if( g_printing_type_entry_changed )
			{
				update_by_printing_type_entry();
			}
		}
		EnableSignal();
	}

	return FALSE;
}

void
on_printing_type_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		g_printing_type_entry_changed = TRUE;

		if( !g_printing_type_popwin_mapped )
		{
			update_by_printing_type_entry();
		}
	}
	EnableSignal();
}

void
on_printing_scaling_spin_changed       (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(editable));
		GtkSpinButton* scaling_spin
			= (GtkSpinButton*)LookupWidget(window, "printing_scaling_spin");
		g_main_window->scaling = (short)scaling_spin->adjustment->value;

//		UpdateWidgets(window, "pringing_scaling_spin");
	}
	EnableSignal();
}

void
on_centering_button_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

		if( GTK_TOGGLE_BUTTON(button)->active )
			g_main_window->centering = LOCATION_CENTER;
		else
			g_main_window->centering = LOCATION_UPPERLEFT;

		UpdateWidgets(window, "centering_button");
	}
	EnableSignal();
}

void
on_borderless_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

		if( GTK_TOGGLE_BUTTON(button)->active )
		{
			short media_type_value = GetCurrentnValue(CNCL_MEDIATYPE);

			if( IsAvailableMediaBorder(g_mediaborder_dialog, media_type_value) )
			{
				gchar* alert_msg
					= LookupText(g_keytext_list, "mediaborder_alert");
				UtilMessageBox(alert_msg, g_window_title,
					MB_OK | MB_ICON_INFORMATION);

				UpdateMenuLink(CNCL_MARGINTYPE, CND_MARGIN_MINUS);
			}
			else
			{
				short new_media_type_value;
				if( (new_media_type_value
						= ShowMediaBorderDialog(g_mediaborder_dialog,
												media_type_value)) != -1 )
				{
					UpdateMenuLink(CNCL_MEDIATYPE, new_media_type_value);
					UpdateMenuLink(CNCL_MARGINTYPE, CND_MARGIN_MINUS);
				}
				else
				{
					gtk_toggle_button_set_active(
						GTK_TOGGLE_BUTTON(button), FALSE);
				}
			}
		}
		else
		{
			UpdateMenuLink(CNCL_MARGINTYPE, CND_MARGIN_NORMAL);
		}

		UpdateWidgets(window, "borderless_button");

#ifdef	GUI_WITH_PIXMAPS
		UpdateDrawingArea(window, "basic_draw_area");
#endif
	}
	EnableSignal();
}

void
on_border_ext_i_button_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(togglebutton));
		g_main_window->ext_border
			= GetActiveButtonIndex(window, g_border_ext_button_name, 3);

		UpdateWidgets(window, "border_ext_button");
	}
	EnableSignal();
}

void
on_copies_spin_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(editable));
		GtkSpinButton* copies_spin
			= (GtkSpinButton*)LookupWidget(window, "copies_spin");
		g_main_window->copies = (short)copies_spin->adjustment->value;

//		UpdateWidgets(window, "copies_spin");
	}
	EnableSignal();
}

void
on_reverse_order_button_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_collate_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}

void
on_default_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	short paper_size_value = GetCurrentnValue(CNCL_PAPERSIZE);
	short margin_type_value = GetCurrentnValue(CNCL_MARGINTYPE);

	FreeDataBase();
	InitDataBase(g_model_name);

	// Initialize the print quality toggle button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
			"quality_standard_button")), TRUE);
	SetQualityCustomValue(g_quality_dialog);

	// Initialize the color adjustment toggle button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
			"color_auto_button")), TRUE);

	// Initialize the print bw toggle button.
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
			"print_bw_button1")), FALSE);
	gtk_toggle_button_set_active(
		GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
			"print_bw_button2")), FALSE);

	// Re-create the color adjustment dialog.
	g_color_dialog
		= ReCreateColorDialog( g_color_dialog, UI_DIALOG(g_main_window));

	// Restore paper size and margin type.
	UpdateMenuLink(CNCL_PAPERSIZE, paper_size_value);
	UpdateMenuLink(CNCL_MARGINTYPE, margin_type_value);

	// Update widgets.
	DisableSignal();
	UpdateWidgets(UI_DIALOG(g_main_window)->window, NULL);
	EnableSignal();

	// Update all of window
	UpdateDialog(UI_DIALOG(g_main_window), NULL);
}


void
on_page_setup_default_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	// Initialize paper size.
	UpdateMenuLink(CNCL_PAPERSIZE, g_main_window->init_paper_size);

	// Re-create the user size dialog.
	g_user_size_dialog = ReCreateUserSizeDialog(
		g_user_size_dialog, UI_DIALOG(g_main_window), g_unit_inch);

	// Initialize printing type.
	g_main_window->printing_type = g_printing_type_value[0];

	// Initialize margin type.
	if( IsAvailableBorderless() )
		UpdateMenuLink(CNCL_MARGINTYPE, CND_MARGIN_NORMAL);

	// Initialize dupelx printing.
	g_duplex_value = CND_DUPLEX_OFF;
	UpdateMenuLink(CNCL_DUPLEX_PRINTING, CND_DUPLEX_OFF);

	// Initialize scaling, etc.
	g_main_window->scaling = 100;
	g_main_window->centering = LOCATION_UPPERLEFT;
	g_main_window->ext_border = GetDefaultExtBorder(g_model_id);
	g_main_window->stapleside = STAPLESIDE_LONG;
	g_main_window->copies = 1;

	// Update widgets.
	DisableSignal();
	UpdateWidgets(UI_DIALOG(g_main_window)->window, NULL);
	EnableSignal();
}

gboolean
on_combo_button_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data)
{
	if( event->type == GDK_2BUTTON_PRESS 
	 || event->type == GDK_3BUTTON_PRESS )
		return TRUE;
	else
		return FALSE;
}



void
on_util_ink_cartridge_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	UtilInkCartridgeSet(&g_uidb);
}


void
on_auto_duplex_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

		if( GTK_TOGGLE_BUTTON(button)->active )
			g_duplex_value = CND_DUPLEX_AUTO;
		else
			g_duplex_value = CND_DUPLEX_OFF;

		UpdateMenuLink(CNCL_DUPLEX_PRINTING, g_duplex_value);
		UpdateWidgets(window, "auto_duplex_button");
	}
	EnableSignal();
}


void
on_longside_button_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

		if( GTK_TOGGLE_BUTTON(button)->active )
			g_main_window->stapleside = STAPLESIDE_LONG;

		UpdateWidgets(window, "stapleside_button");
	}
	EnableSignal();
}


void
on_shortside_button_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	if( DisableSignal() )
	{
		GtkWidget* window = GetTopWidget(GTK_WIDGET(button));

		if( GTK_TOGGLE_BUTTON(button)->active )
			g_main_window->stapleside = STAPLESIDE_SHORT;

		UpdateWidgets(window, "stapleside_button");
	}
	EnableSignal();
}

enum {
	NOTOPAGE_MAIN = 0,
	NOTOPAGE_PAFGESETUP,
	NOTOPAGE_MAINTENANCE
};

void
on_ui_main_notebook_switch_page        (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        gint             page_num,
                                        gpointer         user_data)
{
	// "Page Size" Processing to make display of combo box left justify.
	// Because it is displayed by right adjust after the switch of the tab. 
	// For instance, "Comm. Env.#10 4.12x9.50in 104.6x241.3mm" etc.
	if( page_num == NOTOPAGE_PAFGESETUP) {
		GtkWidget* combo = LookupWidget(UI_DIALOG(g_main_window)->window, "media_size_combo");
		gtk_editable_set_position(GTK_EDITABLE(GTK_COMBO(combo)->entry), 0);
	}
}

