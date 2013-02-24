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


#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "callbacks.h"
#include "bjuidefs.h"
#include "util_setconfig.h"
#include "util_nozzlecheck.h"
#include "util_parse_function.h"
#include "util_com.h"


#ifdef _PRINTUI_DEBUG_
static void display_ui_settings( short format , IPCU ipc );
static void check_ui_setting_and_ipc( short format , IPCU ipc );
#endif

void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
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

/* Ver.3.70 */
/* when dialog is "sensive false", not close dialog */
gboolean
on_ui_window_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	if ( GTK_WIDGET_SENSITIVE( widget )) {
  		return FALSE;
	}
	else {
  		return TRUE;
	}
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
	InitExec_NozzleCheck();
	ExecMaintenance( FUNCTYPE_CLEANING );
}

void
on_util_refresh_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	InitExec_NozzleCheck();
	ExecMaintenance( FUNCTYPE_DEEP_CLEANING );
}

void
on_util_nozzle_check_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	InitExec_NozzleCheck();
	ExecMaintenance( FUNCTYPE_NOZZLE_CHECK );
}

void
on_util_head_adjust_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	if ( IsManualHeadMode() == TRUE ) ExecMaintenance( FUNCTYPE_HEAD_ALIGNMENT_MANUAL );
	else  ExecMaintenance( FUNCTYPE_HEAD_ALIGNMENT_AUTO );
}

void
on_util_roller_clean_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_ROLLER_CLEANING );
}

void
on_util_plate_clean_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_PLATE_CLEANING );
}

void
on_util_power_off_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_POWER_OFF );
}

void
on_util_auto_power_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_AUTOPOWER );
}

void
on_util_config_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_CUSTOM );
}

void
on_util_ink_reset_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_util_ink_warning_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_util_quiet_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_QUIET );
}

void
on_util_ink_cartridge_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_INK_CARTRIDGE );
}

void
on_util_paper_source_setting_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	ExecMaintenance( FUNCTYPE_PAPER_SOURCE_SETTING );
}

