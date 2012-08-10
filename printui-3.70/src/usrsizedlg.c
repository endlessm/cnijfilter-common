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

#include "callbacks.h"
#ifndef	USE_LIB_GLADE
#	include "interface.h"
#	include "support.h"
#endif

#include "bjuidefs.h"


static const gchar* user_size_scale_button_name[] =
{
	"user_size_scale_mm_button",
	"user_size_scale_inch_button",
	NULL
};


/* Ver.280 */
static const gchar* user_size_scale_format_res[] =
{
	"custom_size_mm_format",
	"custom_size_inches_format",
	NULL
};

static const gchar* user_size_range_format[] =
{
	"%4.1f",
	"%4.2f",
	NULL
};

static
double Milli2Inch(double min_mm, double max_mm,
					double min_in, double max_in, double value)
{
	double inch = (value - min_mm) * (max_in - min_in)
				/ (max_mm - min_mm) + min_in;

	if( inch < min_in )	inch = min_in;
	if( inch > max_in )	inch = max_in;

	return inch;
}

static
double Inch2Milli(double min_in, double max_in,
					double min_mm, double max_mm, double value)
{
	double milli = (value - min_in) * (max_mm - min_mm)
				 / (max_in - min_in) + min_mm;

	if( milli < min_mm )	milli = min_mm;
	if( milli > max_mm )	milli = max_mm;

	return milli;
}

static
double Long2Double(long value)
{
	return (double)value / 100.0;
}

static
long Double2Long(double value)
{
	return (long)(value * 100.0 + 0.5);
}

static
double MakeInchScale(double value)
{
	return value;
//	return (double)((long)(value * 100.0 + 0.5)) / 100.0;
}

UIUserSizeDialog* CreateUserSizeDialog(UIDialog* parent, gboolean unit_inch)
{
	UIUserSizeDialog* dialog
		 = (UIUserSizeDialog*)CreateDialog(sizeof(UIUserSizeDialog), parent);

#ifdef	USE_LIB_GLADE
	UI_DIALOG(dialog)->window = LookupWidget(NULL, "user_size_dialog");
#else
	UI_DIALOG(dialog)->window = create_user_size_dialog();
#endif

	// 1:inches, 0:mm
	dialog->scale = dialog->old_scale = unit_inch? 1 : 0;
	dialog->width  = Long2Double(g_user_paper_size[YOKO]);
	dialog->height = Long2Double(g_user_paper_size[TATE]);

	return dialog;
}

UIUserSizeDialog* ReCreateUserSizeDialog(UIUserSizeDialog* dialog,
								 UIDialog* parent, gboolean unit_inch)
{
	// Reset the default user size.
	InitUserPaperSize();

	DisposeDialog((UIDialog*)dialog);
	return CreateUserSizeDialog(parent, unit_inch);
}

void ShowUserSizeDialog(UIUserSizeDialog* dialog)
{
	GtkWidget* button;

	button = LookupWidget(UI_DIALOG(dialog)->window,
				user_size_scale_button_name[dialog->scale]);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);

	dialog->min_mm_w = Long2Double(g_bj_paper_size.nMinCustomWidth);
	dialog->max_mm_w = Long2Double(g_bj_paper_size.nMaxCustomWidth);
	dialog->min_mm_h = Long2Double(g_bj_paper_size.nMinCustomLength);
	dialog->max_mm_h = Long2Double(g_bj_paper_size.nMaxCustomLength);
	dialog->min_in_w = MakeInchScale(dialog->min_mm_w / 25.4);
	dialog->max_in_w = MakeInchScale(dialog->max_mm_w / 25.4);
	dialog->min_in_h = MakeInchScale(dialog->min_mm_h / 25.4);
	dialog->max_in_h = MakeInchScale(dialog->max_mm_h / 25.4);

	UpdateUserSizeWidgets(dialog, TRUE);
	ShowDialog((UIDialog*)dialog, "user_size_ok_button");
}

void HideUserSizeDialog(UIUserSizeDialog* dialog, gboolean apply)
{
	if( apply )
	{
		ApplyUserSizeDialog(dialog);
	}
   	HideDialog((UIDialog*)dialog);
}

void ApplyUserSizeDialog(UIUserSizeDialog* dialog)
{
	GtkSpinButton* width_spin
		= (GtkSpinButton*)LookupWidget(
			UI_DIALOG(dialog)->window, "user_size_width_spin");
	GtkSpinButton* height_spin
	 	= (GtkSpinButton*)LookupWidget(
			UI_DIALOG(dialog)->window, "user_size_height_spin");

	GtkAdjustment* adjust_w = width_spin->adjustment;
	GtkAdjustment* adjust_h = height_spin->adjustment;

	dialog->scale
		= GetActiveButtonIndex(
			UI_DIALOG(dialog)->window, user_size_scale_button_name, 0);

	if( dialog->scale )
	{	// inch -> mm
		dialog->width = Inch2Milli(dialog->min_in_w, dialog->max_in_w,
						dialog->min_mm_w, dialog->max_mm_w, adjust_w->value);
		dialog->height = Inch2Milli(dialog->min_in_h, dialog->max_in_h,
						dialog->min_mm_h, dialog->max_mm_h, adjust_h->value);
	}
	else
	{
		dialog->width = adjust_w->value;
		dialog->height = adjust_h->value;
	}

	g_user_paper_size[YOKO] = Double2Long(dialog->width);
	g_user_paper_size[TATE] = Double2Long(dialog->height);
}

void UpdateUserSizeWidgets(UIUserSizeDialog* dialog, gboolean init_flag)
{
	GtkSpinButton* width_spin
		= (GtkSpinButton*)LookupWidget(
			UI_DIALOG(dialog)->window, "user_size_width_spin");
	GtkSpinButton* height_spin
	 	= (GtkSpinButton*)LookupWidget(
			UI_DIALOG(dialog)->window, "user_size_height_spin");

	GtkAdjustment* adjust_w = width_spin->adjustment;
	GtkAdjustment* adjust_h = height_spin->adjustment;

	double min_w, max_w;
	double min_h, max_h;
	double new_w, new_h;
	GtkWidget* label;
	gchar scale_label[64];
	gchar* scale_string;
	gchar width_min_string[12];
	gchar width_max_string[12];
	gchar height_min_string[12];
	gchar height_max_string[12];
	/* Ver.3.00 */
	double min_w_adjust, max_w_adjust;
	double min_h_adjust, max_h_adjust;
	gchar width_min_string_adjust[12];
	gchar width_max_string_adjust[12];
	gchar height_min_string_adjust[12];
	gchar height_max_string_adjust[12];

	// The scale of dialog->width and dialog->height is "mm", 
	// so old_scale must be 0 when showing this dialog.
	int old_scale = (init_flag)? 0 : dialog->old_scale;
	int new_scale
		= GetActiveButtonIndex(
			UI_DIALOG(dialog)->window, user_size_scale_button_name, 0);

	if( init_flag )
	{
		adjust_w->value = dialog->width;
		adjust_h->value = dialog->height;
	}

	if( new_scale )
	{	// inch
		width_spin->climb_rate = height_spin->climb_rate = 0.01;
		width_spin->digits = height_spin->digits = 2;

		if( new_scale != old_scale )
		{	//  mm -> inch
			new_w = Milli2Inch(dialog->min_mm_w, dialog->max_mm_w,
					dialog->min_in_w, dialog->max_in_w, adjust_w->value);
			new_h = Milli2Inch(dialog->min_mm_h, dialog->max_mm_h,
					dialog->min_in_h, dialog->max_in_h, adjust_h->value);
		}
		else
		{
			new_w = adjust_w->value;
			new_h = adjust_h->value;
		}
		min_w = dialog->min_in_w;
		max_w = dialog->max_in_w;
		min_h = dialog->min_in_h;
		max_h = dialog->max_in_h;
	}
	else
	{	// mm
		width_spin->climb_rate = height_spin->climb_rate = 0.1;
		width_spin->digits = height_spin->digits = 1;

		if( new_scale != old_scale )
		{	//  inch -> mm
			new_w = Inch2Milli(dialog->min_in_w, dialog->max_in_w,
					dialog->min_mm_w, dialog->max_mm_w, adjust_w->value);
			new_h = Inch2Milli(dialog->min_in_h, dialog->max_in_h,
					dialog->min_mm_h, dialog->max_mm_h, adjust_h->value);
		}
		else
		{
			new_w = adjust_w->value;
			new_h = adjust_h->value;
		}
		min_w = dialog->min_mm_w;
		max_w = dialog->max_mm_w;
		min_h = dialog->min_mm_h;
		max_h = dialog->max_mm_h;
	}

	// Set adjustment fields.
	adjust_w->step_increment = width_spin->climb_rate;
	adjust_h->step_increment = height_spin->climb_rate;
	adjust_w->page_increment = width_spin->climb_rate * 10;
	adjust_h->page_increment = height_spin->climb_rate * 10;

#if 0
	adjust_w->lower = min_w;
	adjust_w->upper = max_w;
	adjust_h->lower = min_h;
	adjust_h->upper = max_h;
#endif

	/* Ver.3.00 */
	if( new_scale )	//inch
	{
		snprintf( width_min_string_adjust, 12, "%6.0f", (float)min_w * (float)100 );
		snprintf( width_max_string_adjust, 12, "%6.0f", (float)max_w * (float)100 );
		snprintf( height_min_string_adjust, 12,  "%6.0f", (float)min_h * (float)100 );
		snprintf( height_max_string_adjust, 12,  "%6.0f", (float)max_h * (float)100 );

		min_w_adjust = (double)atoi( width_min_string_adjust ) / (double)100;
		max_w_adjust = (double)atoi( width_max_string_adjust ) / (double)100;
		min_h_adjust = (double)atoi( height_min_string_adjust ) / (double)100;
		max_h_adjust = (double)atoi( height_max_string_adjust ) / (double)100;

	}
	else		//mm
	{
		snprintf( width_min_string_adjust, 12, "%6.0f", (float)min_w * (float)10 );
		snprintf( width_max_string_adjust, 12, "%6.0f", (float)max_w * (float)10 );
		snprintf( height_min_string_adjust,12,  "%6.0f", (float)min_h * (float)10 );
		snprintf( height_max_string_adjust, 12, "%6.0f", (float)max_h * (float)10 );
	
		min_w_adjust = (double)atoi( width_min_string_adjust ) / (double)10;
		max_w_adjust = (double)atoi( width_max_string_adjust ) / (double)10;
		min_h_adjust = (double)atoi( height_min_string_adjust ) / (double)10;
		max_h_adjust = (double)atoi( height_max_string_adjust ) / (double)10;
	}

	adjust_w->lower = min_w_adjust;
	adjust_w->upper = max_w_adjust;
	adjust_h->lower = min_h_adjust;
	adjust_h->upper = max_h_adjust;


#ifdef _PRINTUI_DEBUG_
	fprintf(stderr,"adjust_w->lower = %f\n",adjust_w->lower);
	fprintf(stderr,"min_w = %f\n",min_w);
	fprintf(stderr,"adjust_w->upper = %f\n",adjust_w->upper);
	fprintf(stderr,"max_w = %f\n",max_w);
	fprintf(stderr,"adjust_h->lower = %f\n",adjust_h->lower);
	fprintf(stderr,"min_h = %f\n",min_h);
	fprintf(stderr,"adjust_h->upper = %f\n",adjust_h->upper);
	fprintf(stderr,"max_h = %f\n",max_h);
#endif

	gtk_spin_button_set_value(width_spin, new_w);
	gtk_spin_button_set_value(height_spin, new_h);


	/* Ver.2.80 */
	snprintf( width_min_string, 12, user_size_range_format[new_scale], (float)min_w );
	snprintf( width_max_string, 12, user_size_range_format[new_scale], (float)max_w );
	snprintf( height_min_string, 12, user_size_range_format[new_scale], (float)min_h );
	snprintf( height_max_string, 12, user_size_range_format[new_scale], (float)max_h );

	scale_string = LookupText(g_keytext_list, user_size_scale_format_res[new_scale]);

	// Width scale label.
	label = LookupWidget(UI_DIALOG(dialog)->window, "user_size_width_label");
	snprintf(scale_label, sizeof(scale_label), scale_string, width_min_string, width_max_string );/*Ver.2.90(s)*/
	gtk_label_set_text(GTK_LABEL(label), scale_label);

	// Height scale label.
	label = LookupWidget(UI_DIALOG(dialog)->window, "user_size_height_label");
	snprintf(scale_label,sizeof(scale_label), scale_string, height_min_string, height_max_string );/*Ver.2.90(s)*/
	gtk_label_set_text(GTK_LABEL(label), scale_label);


	dialog->old_scale = new_scale;
}

gboolean
on_user_size_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	HideUserSizeDialog(g_user_size_dialog, FALSE);
	return TRUE;
}

void
on_user_size_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	HideUserSizeDialog(g_user_size_dialog, TRUE);
}

void
on_user_size_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	HideUserSizeDialog(g_user_size_dialog, FALSE);
}

void
on_user_size_scale_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	if( GTK_TOGGLE_BUTTON(button)->active )
		UpdateUserSizeWidgets(g_user_size_dialog, FALSE);
}

