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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


gboolean SameName(gchar* name1, gchar* name2)
{
	if( name1 != NULL && name2 != NULL )
		return strcmp(name1, name2)? FALSE : TRUE;
	else
		return FALSE;
}

GtkWidget* LookupWidget(GtkWidget* window, const gchar* name)
{
#ifdef	USE_LIB_GLADE
	return glade_xml_get_widget(g_ui_xml, name);
#else
	return lookup_widget(window, name);
#endif
}

GtkWidget* GetTopWidget(GtkWidget* widget) 
{
	return gtk_widget_get_toplevel(widget);
}

void UpdateWidgets(GtkWidget* window, gchar* except_name)
{
	char *current_comb_supply = NULL;
	char *current_comb_supply_local = NULL;
	short	len = 0;
	short	current_comb_supply_id = 0;
	
#ifdef _PRINTUI_DEBUG_
	fprintf(stderr,"\n### UpdateWidgets :except_name = %s ###\n",except_name);
#endif

	/* Ver.2.70: for "Front for Plain" */
	{
		/* Store "media_supply_entry" setting(UI strings) */
		GtkWidget* entry = LookupWidget(window, "media_supply_entry");
		current_comb_supply = (char*)gtk_entry_get_text(GTK_ENTRY(entry));
		len = strlen(current_comb_supply) + 1;
		current_comb_supply_local = malloc( len );
		memset(current_comb_supply_local,0x00, len );
	
		strncpy( current_comb_supply_local , current_comb_supply , len );
		current_comb_supply_local[len-1] = '\0';
#ifdef _PRINTUI_DEBUG_
		fprintf(stderr,"current_comb_supply_local = %s\n",current_comb_supply_local);
#endif
	}
	
	// Print bw button
	if( !SameName(except_name, "print_bw_button") )
	{
		gboolean sensitive = TRUE;

		switch( GetCurrentnValue(CNCL_GRAYSCALE) )
		{
		case CND_BJGRAYSCALE_OFF:
			break;
		case CND_BJGRAYSCALE_ON:
			break;
		case CND_BJGRAYSCALE_GRAY:
			sensitive = FALSE;
			break;
		default:
			break;
		}

		gtk_widget_set_sensitive( LookupWidget(window, "print_bw_button1"), sensitive);
		gtk_widget_set_sensitive( LookupWidget(window, "print_bw_button2"), sensitive);
	}

	// Media type combo
	if( !SameName(except_name, "media_type_combo") )
	{
		GList* glist = GetComboList(CNCL_MEDIATYPE);
		SetGListToCombo(window, "media_type_combo", glist, GetCurrentString(CNCL_MEDIATYPE));
	}

	// Media supply combo
	if( !SameName(except_name, "media_supply_combo") )
	{
		GList* glist = GetComboList(CNCL_MEDIASUPPLY);
		/* iP3300,MP510FAdd "Front for Plain" (This value is always available) */
		{
			char *str;
		
			//GetAllFlagsFIf CND_SUPPLY_CASSETTE_04 exist --> str > 0
			if( GetAllFlags( CNCL_MEDIASUPPLY , CND_SUPPLY_CASSETTE_04 ) >= 0 ){
				str = ValueToName( CNCL_MEDIASUPPLY , CND_SUPPLY_FRONT_FOR_PLAIN );
				glist = g_list_append(glist, str);
			}
		}
		
		/* Ver.2.70: for "Front for Plain" */
		if( except_name!=NULL ){
			/* UI setting at the top of this function is not disable on CNCLDB --> use it (to UI) */
			/* UI setting at the top of this function is disable on CNCLDB     --> use current value of CNCLDB (to UI) */
			current_comb_supply_id = NameToValue( CNCL_MEDIASUPPLY , current_comb_supply_local );

			/* Replace "CND_SUPPLY_FRONT_FOR_PLAIN" with "CND_SUPPLY_ASF" before check */
			if( current_comb_supply_id == CND_SUPPLY_FRONT_FOR_PLAIN ) current_comb_supply_id = CND_SUPPLY_ASF;
		
			if( IsAvailableValue( CNCL_MEDIASUPPLY , current_comb_supply_id ) ){ /* UI setting is not disable on CNCLDB */
				SetGListToCombo(window, "media_supply_combo",glist, current_comb_supply_local );
			}else{ 																 /* UI setting is disable on CNCLDB */
#ifdef _PRINTUI_DEBUG_
		fprintf(stderr," IsAvailableValue(%s,ID=%d): not Available!!\n",current_comb_supply_local,current_comb_supply_id);
#endif
				SetGListToCombo(window, "media_supply_combo",glist, GetCurrentString(CNCL_MEDIASUPPLY));
			}
		}
		else{	//NULL --> Select "CNCLDB current value" on UI
			SetGListToCombo(window, "media_supply_combo",glist, GetCurrentString(CNCL_MEDIASUPPLY));
		}
	}

	// Cartridge type combo
	if( !SameName(except_name, "cartridge_type_combo") )
	{
		GList* glist = GetComboList(CNCL_CARTRIDGE);
		SetGListToCombo(window, "cartridge_type_combo", glist, GetCurrentString(CNCL_CARTRIDGE));
	}

	// Quality radio button
	{
		gboolean custom_active = GTK_TOGGLE_BUTTON( LookupWidget(window, "quality_custom_button"))->active;
		GtkWidget* custom_button  = LookupWidget(window, "quality_dialog_button");
		short quality = GetCurrentnValue(CNCL_PRINTQUALITY);
		GtkWidget* button;
		short value[3];
		int i;

		for( i = 0 ; i < 3 ; i++ )
		{
			button = LookupWidget(window, g_quality_button_name[i]);
			value[i] = GetCurrentnValue(g_mess_map[i]);

			if( !custom_active && value[i] == quality )
			{	// activate button
				gtk_widget_set_sensitive(custom_button, FALSE);
				gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
			}

			if( value[i] != CND_QUALITY_ABSOLUTE_NA )
				gtk_widget_set_sensitive(button, TRUE);
			else
				gtk_widget_set_sensitive(button, FALSE);
		}

		if( custom_active ){	// activate custom button
			gtk_widget_set_sensitive(custom_button, TRUE);
		}
	}

	// Color auto radio button
	{
		GtkWidget* button = LookupWidget(window, "color_auto_button");
		gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(button), g_main_window->color_auto );
		
	}
	// Color adjust radio button
	{
		GtkWidget* button = LookupWidget(window, "color_dialog_button");

		if( GTK_TOGGLE_BUTTON( LookupWidget(window, "color_manual_button"))->active )
			gtk_widget_set_sensitive(button, TRUE);
		else
			gtk_widget_set_sensitive(button, FALSE);
	}

	// Guide(Thickness etc...)
	{
		GtkWidget* label = LookupWidget(window, "thick_msg_label");
		char* position_msg = GetCurrentString(CNCL_MESS_THICK);

		gtk_label_set_text(GTK_LABEL(label), (gchar*)position_msg);
	}

	// Paper gap combo
	if( !SameName(except_name, "paper_gap_combo") )
	{
		GList* glist = GetComboList(CNCL_PAPERGAP_COMMAND);
		SetGListToCombo(window, "paper_gap_combo", glist, GetCurrentString(CNCL_PAPERGAP_COMMAND));
	}

	/////////////////////////////////////////////////////////////////

	// Media size combo
	if( !SameName(except_name, "media_size_combo") )
	{
		short margin_type = GetCurrentnValue(CNCL_MARGINTYPE);
		if( margin_type == CND_MARGIN_MINUS )
		{
			// Page size is displayed. ( boderless )
			SetGListToCombo(window, "media_size_combo", g_paper_size_margin_list, GetCurrentString(CNCL_PAPERSIZE));
		}
		else
		{
			// Page size is displayed. ( All "page size" )
			SetGListToCombo(window, "media_size_combo", g_paper_size_list, GetCurrentString(CNCL_PAPERSIZE));
		}
	}

	// Printing type combo
	if( !SameName(except_name, "printing_type_combo") )
	{
		SetTextArrayToCombo(window, "printing_type_combo",
			(const gchar**)g_printing_type_name,
			(const short*)g_printing_type_value,
				g_main_window->printing_type);
	}

	// Printing scaling hbox.
	{
		GtkWidget* hbox = LookupWidget(window, "scaling_hbox");

		if( g_main_window->printing_type == PRINTING_TYPE_SCALE )
			gtk_widget_show(hbox);
		else
			gtk_widget_hide(hbox);
	}

	// Printing scaling spin.
	if( !SameName(except_name, "printing_scaling_button") )
	{
		GtkSpinButton* scaling_spin = (GtkSpinButton*)LookupWidget(window, "printing_scaling_spin");
		gtk_adjustment_set_value(scaling_spin->adjustment, (gfloat)g_main_window->scaling);
	}

	// Centering button.
	if( !SameName(except_name, "centering_button") )
	{
		gboolean active
			= (g_main_window->centering == LOCATION_CENTER)? TRUE : FALSE;
		gtk_toggle_button_set_active(
			GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
				"centering_button")), active);
	}

	if( IsAvailableBorderless() )
	{
		short margin_type = GetCurrentnValue(CNCL_MARGINTYPE);
		gboolean active = (margin_type == CND_MARGIN_MINUS)? TRUE : FALSE;

		// Borderless hbox.
		GtkWidget* hbox = LookupWidget(window, "borderless_hbox");
//		gtk_widget_set_sensitive(hbox, active);
		if( active == TRUE )
			gtk_widget_show(hbox);
		else
			gtk_widget_hide(hbox);

		// Borderless button.
		if( !SameName(except_name, "borderless_button") )
		{
			GtkWidget* button = LookupWidget(window, "borderless_button");
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), active);
		}

		// Border ext button.
		if( !SameName(except_name, "border_ext_button") )
		{
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
				g_border_ext_button_name[g_main_window->ext_border])), TRUE);
		}
	}

	if( IsAvailableDuplex() )
	{
		GtkWidget* duplex_vbox;
		GtkWidget* duplex_hbox;
		gboolean active;

		// Duplex vbox.
		duplex_vbox = LookupWidget(window, "duplex_vbox");
		gtk_widget_set_sensitive(duplex_vbox, IsAvailableValue(CNCL_DUPLEX_PRINTING, CND_DUPLEX_AUTO));

		// Duplex hbox.
		active = (CND_DUPLEX_AUTO == GetCurrentnValue(CNCL_DUPLEX_PRINTING))? TRUE : FALSE;	/* Ver.2.70 */
		duplex_hbox = LookupWidget(window, "duplex_hbox");
		gtk_widget_set_sensitive(duplex_hbox, active);

		// Auto Duplex button.
		if( !SameName(except_name, "auto_duplex_button") )
		{
		//	GtkWidget* button = LookupWidget(window, "auto_duplex_button");	// not in use...
		}

		// Stapleside
		if( !SameName(except_name, "stapleside_button") )
		{
			gtk_toggle_button_set_active(
				GTK_TOGGLE_BUTTON(LookupWidget(UI_DIALOG(g_main_window)->window,
				g_staple_button_name[g_main_window->stapleside])), TRUE);
		}
	}

	// Copies spin.
	if( !SameName(except_name, "copies_spin") )
	{
		GtkSpinButton* copies_spin = (GtkSpinButton*)LookupWidget(window, "copies_spin");
		gtk_adjustment_set_value(copies_spin->adjustment, (gfloat)g_main_window->copies);
	}
	

	if(current_comb_supply_local){
		free(current_comb_supply_local);
		current_comb_supply_local = NULL;
	}
	
}

void InitSignal()
{
	g_valid_signal = 0;
}

gboolean EnableSignal()
{
	if( g_valid_signal > 0 )
		g_valid_signal--;

	return (g_valid_signal)? FALSE : TRUE;
}

gboolean DisableSignal()
{
	return (g_valid_signal++)? FALSE : TRUE;
}

int GetActiveButtonIndex(GtkWidget* window,
			 const gchar* button_name[], int default_index)
{
	GtkWidget* button;
	int index = 0;

	while( button_name[index] )
	{
		if( (button = LookupWidget(window, button_name[index])) != NULL )
		{
			if( GTK_TOGGLE_BUTTON(button)->active )
				return index;
		}
		index++;
	}
	return default_index;
}

void SetPopdownStringsToCombo(GtkWidget *combo, GList *glist, int focus_index)
{
	GList *p = glist;
	GtkWidget *label;
	int index = 0;

	gtk_list_clear_items(GTK_LIST(GTK_COMBO(combo)->list), 0, -1);

	while( p != NULL )
	{
		label = gtk_list_item_new_with_label((gchar*)p->data);
		gtk_container_add(GTK_CONTAINER(GTK_COMBO(combo)->list), label);
		gtk_widget_show(label);

		if( index == focus_index )
			gtk_widget_grab_focus(label);

		p = p->next;
		index++;
	}
}

void SetGListToCombo(GtkWidget* window, gchar *combo_name,
									GList* glist, gchar* current)
{
	GtkWidget* combo = LookupWidget(window, combo_name);

	if( glist != NULL && current != NULL )
	{
		/* Ver.2.70 */
		GList *p = glist;
		int index = 0;
		int find = FALSE;
		while( p != NULL )
		{
			if( strcmp((gchar*)p->data, current) == 0 )
			{
				find = TRUE;
				break;
			}
			index++;
			p = p->next;
		}
		if( find != TRUE )
			index = 0;

//		gtk_combo_set_popdown_strings(GTK_COMBO(combo), glist);
		SetPopdownStringsToCombo(combo, glist, index);
		/* Ver.2.70end */

		gtk_entry_set_text(GTK_ENTRY(GTK_COMBO(combo)->entry), current);
		gtk_editable_set_position(GTK_EDITABLE(GTK_COMBO(combo)->entry), 0);
	}
}

void SetTextArrayToCombo(GtkWidget* window, gchar *combo_name,
		const gchar* key_array[], const short value_array[], short value)
{
	GList* glist = NULL;
	int index = 0;
	int i;

	for( i = 0 ; key_array[i] != NULL ; i++ )
	{
		glist = g_list_append(glist, LookupText(g_keytext_list, key_array[i]));

		if( value_array[i] == value )
			index = i;
	}

	SetGListToCombo(window, combo_name, glist, g_list_nth_data(glist, index));
}

int GetTextArrayValueFromCombo(GtkWidget* window, gchar *combo_name,
		const gchar* key_array[], const short value_array[])
{
	GtkWidget* combo = LookupWidget(window, combo_name);
	const gchar* current = gtk_entry_get_text(GTK_ENTRY(GTK_COMBO(combo)->entry));
	int i;

	for( i = 0 ; key_array[i] != NULL ; i++ )
	{
		if( !strcmp(current, LookupText(g_keytext_list, key_array[i])) )
		{
			return value_array[i];
		}
	}
	return 0;
}

#ifdef	GUI_WITH_PIXMAPS
void UpdateDrawingArea(GtkWidget* window, const gchar* name)
{

	GtkWidget* area;
	gint area_w, area_h;
	GdkRectangle area_rect;

	if( (area = LookupWidget(window, name)) != NULL )
	{
		if( area->window != NULL )
		{
			gdk_window_get_size(area->window, &area_w, &area_h);
			area_rect.x = 0;
			area_rect.y = 0;
			area_rect.width = area_w;
			area_rect.height = area_h;
			gtk_widget_draw(area, &area_rect);
		}
	}
}
#endif

void UpdateScaleValue(GtkWidget* window, GtkAdjustment* adjust, gchar* name)
{
	GtkWidget* label = LookupWidget(window, name);
	gchar value[8];

	sprintf(value, "%3d", (int)adjust->value);
	gtk_label_set_text(GTK_LABEL(label), (gchar*)value);
}

#define	NO_PRINT_COLOR_ICON

#define	BODY_PIXMAP_X		10
#define	BODY_PIXMAP_Y		19
#define	L_GUIDE_PIXMAP_X	62
#define	L_GUIDE_PIXMAP_Y	7
#define	R_GUIDE_PIXMAP_X	114
#define	R_GUIDE_PIXMAP_Y	7

#ifndef	NO_PRINT_COLOR_ICON
#define COLOR_TEXT_X		45
#define COLOR_TEXT_Y		210
#define MEDIA_TEXT_X		45
#define MEDIA_TEXT_Y		228
#else
#define COLOR_TEXT_X		15
#define COLOR_TEXT_Y		210
#define MEDIA_TEXT_X		15
#define MEDIA_TEXT_Y		228
#endif
#define COLOR_PIXMAP_X		11
#define COLOR_PIXMAP_Y		199

void DrawPrinterDrawingArea(GtkWidget* window, GtkWidget* area)
{
	GdkWindow* area_window = area->window;
	GdkPixmap* pixmap;
	GdkBitmap* mask;
	gchar* xpm_name;
	gchar* key_str;
	gchar* message_str;
	GdkGC* gc = gdk_gc_new(window->window);

	// Background pattern.
	pixmap = LoadPixmap(window, NULL, "bg.xpm");
	DrawPixmap(area_window, gc, 0, 0, pixmap, NULL);
	FreePixmap(pixmap, NULL);

	// Printer body.
	pixmap = LoadPixmap(window, &mask, "printer.xpm");
	DrawPixmap(area_window, gc,
				 BODY_PIXMAP_X, BODY_PIXMAP_Y, pixmap, mask);
	FreePixmap(pixmap, mask);

	// Paper set and out.
	// Right guide(Paper set).
	{
		gchar* in_xpm_name;
		gchar* out_xpm_name;
		gchar* guide_xpm_name;
		short supply = GetCurrentnValue(CNCL_MEDIASUPPLY);
#ifdef	SUPPORT_BANNER
		short media = GetCurrentnValue(CNCL_MEDIATYPE);
#endif
		short size = GetCurrentnValue(CNCL_PAPERSIZE);

		if( supply == CND_SUPPLY_MANUAL )
			in_xpm_name = "in_m.xpm";
		else
			in_xpm_name = NULL;

#ifdef	SUPPORT_BANNER
		if( media == CND_MEDIA_BANNER )
			guide_xpm_name = "guide_a3.xpm";
		else
#endif
			guide_xpm_name = NULL;

		if( GetPaperWidth(size) > GetPaperHeight(size) )
		{
			if( in_xpm_name == NULL )
				in_xpm_name = "in_l.xpm";
			if( guide_xpm_name == NULL )
				guide_xpm_name = "guide_a2.xpm";
			out_xpm_name = "out_ph.xpm";
		}
		else
		{
			if( in_xpm_name == NULL )
				in_xpm_name = "in_p.xpm";
			if( guide_xpm_name == NULL )
				guide_xpm_name = "guide_a1.xpm";
			out_xpm_name = "out_pv.xpm";
		}

		pixmap = LoadPixmap(window, &mask, in_xpm_name);
		DrawPixmap(area_window, gc,
				 BODY_PIXMAP_X, BODY_PIXMAP_Y, pixmap, mask);
		FreePixmap(pixmap, mask);

		pixmap = LoadPixmap(window, &mask, out_xpm_name);
		DrawPixmap(area_window, gc,
				 BODY_PIXMAP_X, BODY_PIXMAP_Y, pixmap, mask);
		FreePixmap(pixmap, mask);

		pixmap = LoadPixmap(window, &mask, guide_xpm_name);
		DrawPixmap(area_window, gc,
				 R_GUIDE_PIXMAP_X, R_GUIDE_PIXMAP_Y, pixmap, mask);
		FreePixmap(pixmap, mask);
	}


	// Left guide(Thickness).
	{
		short thick = GetCurrentnValue(CNCL_MESS_THICK);

		switch( thick )
		{
		case CND_TMESSAGE_UPPER2:
			xpm_name = "guide_b1.xpm";
			break;
		default:
			xpm_name = "guide_b3.xpm";
			break;
		}

		pixmap = LoadPixmap(window, &mask, xpm_name);
		DrawPixmap(area_window, gc,
			 L_GUIDE_PIXMAP_X, L_GUIDE_PIXMAP_Y, pixmap, mask);
		FreePixmap(pixmap, mask);
	}

	// Media type message.
	message_str = GetCurrentString(CNCL_MEDIATYPE);

	DrawString(area_window, g_main_font, gc,
			 MEDIA_TEXT_X, MEDIA_TEXT_Y, message_str);

	{
		if( IsGrayPrint(g_main_window) )
		{
			xpm_name = "print_mono.xpm";
			key_str = "print_mono_message";
		}
		else
		{
			xpm_name = "print_color.xpm";
			key_str = "print_color_message";
		}

#ifndef	NO_PRINT_COLOR_ICON
		// Print color icon.
		pixmap = LoadPixmap(window, &mask, xpm_name);
		DrawPixmap(area_window, gc,
				 COLOR_PIXMAP_X, COLOR_PIXMAP_Y, pixmap, mask);
		FreePixmap(pixmap, mask);
#endif	
		// Color type message.
		message_str = LookupText(g_keytext_list, key_str);
		DrawString(area_window, g_main_font, gc,
				 COLOR_TEXT_X, COLOR_TEXT_Y, message_str);
	}

	gdk_gc_unref(gc);
}

#define QUALITY_PIXMAP_X		30
#define QUALITY_PIXMAP_Y		10

void DrawQualityDrawingArea(GtkWidget* window, GtkWidget* area)
{
	GdkWindow* area_window = area->window;
	GdkGC* gc = gdk_gc_new(window->window);
	GdkPixmap* pixmap;
	GdkBitmap* mask;
	int quality;
	const gchar* button_name[] =
	{
		"quality_high_button",
		"quality_standard_button",
		"quality_draft_button",
		"quality_custom_button",
		NULL
	};
	const gchar* xpm_name[] = 
	{
		"quality_best.xpm",
		"quality_best_color.xpm",
		"quality_normal.xpm",
		"quality_normal_color.xpm",
		"quality_draft.xpm",
		"quality_draft_color.xpm",
		"quality_custom.xpm",
		"quality_custom_color.xpm"
	};

	quality = GetActiveButtonIndex(window, button_name, 0) << 1;

	if( !IsGrayPrint(g_main_window) )
		quality++;

	pixmap = LoadPixmap(window, &mask, xpm_name[quality]);
	DrawPixmap(area_window, gc,
			 QUALITY_PIXMAP_X, QUALITY_PIXMAP_Y, pixmap, mask);
	FreePixmap(pixmap, mask);

	gdk_gc_unref(gc);
}

