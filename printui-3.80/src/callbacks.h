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

void
on_ui_window_destroy                   (GtkObject       *object,
                                        gpointer         user_data);

void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_cancel_button_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_help_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_clean_button_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_refresh_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_nozzle_check_button_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_head_adjust_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_roller_clean_button_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_power_off_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_auto_power_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);
void
on_util_config_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_ink_reset_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_ink_warning_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_quiet_button_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_version_dlg_ok_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);
void
on_version_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_version_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
void
on_util_plate_clean_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

//-------------------------------------------------------------
// Utilities
//-------------------------------------------------------------

void
on_util_ink_cartridge_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_paper_source_setting_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);


gboolean
on_regi_common_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_regi_common_type001_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_drawingarea_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_drawingarea_button_press_event
                                        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_01
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_01
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_02
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_02
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_03
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_03
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_04
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_04
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_05
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_05
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_06
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_06
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_07
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_07
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_08
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_08
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_09
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_09
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_11
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_11
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_12
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_12
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_13
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_13
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_14
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_14
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_15
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_15
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_16
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_16
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_17
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_17
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_18
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_18
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_19
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_19
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_21
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_21
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_22
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_22
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_23
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_23
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_24
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_24
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_25
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_25
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_26
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_26
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_27
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_27
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_28
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_28
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button_changed_29
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_common_type001_button_focus_in_event_29
                                        (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_common_type001_button1_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type001_button2_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type002_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_regi_common_type002_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_regi_common_type002_button1_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type002_button2_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type002_button3_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type002_button4_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_regi_common_type002_button5_clicked (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_setconfig_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_setconfig_type001_dialog_destroy
                                        (GtkObject       *object,
                                        gpointer         user_data);

void
on_setconfig_type001_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_setconfig_type001_button1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_button2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_button3_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_setconfig_type003_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_setconfig_type003_dialog_destroy    (GtkObject       *object,
                                        gpointer         user_data);

void
on_setconfig_type003_dialog_combo_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_setconfig_type003_button1_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type003_button2_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type003_button3_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_02_dialog_destroy (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_setconfig_type001_02_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_setconfig_type001_02_button1_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_02_button2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_cleaning_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_cleaning_type001_dialog_destroy     (GtkObject       *object,
                                        gpointer         user_data);

void
on_cleaning_type001_button001_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_cleaning_type001_button002_clicked  (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_nozzle_check_type001_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_nozzle_check_type001_dialog_destroy (GtkObject       *object,
                                        gpointer         user_data);

void
on_nozzle_check_type001_button001_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_nozzle_check_type001_button002_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_nozzle_check_type002_dialog_destroy (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_nozzle_check_type002_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_nozzle_check_type002_button001_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_nozzle_check_type002_button002_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_button1_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_button2_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_button3_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_checkbutton3_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_setconfig_type001_radiobutton50x_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_setconfig_type001_checkbutton4_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_c_dlg_y_value_spin2_state_changed   (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_c_dlg_m_value_spin2_state_changed   (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_c_dlg_c_value_spin2_state_changed   (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_c_dlg_density_value_spin2_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_c_dlg_contrast_value_spin2_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_c_dlg_tone_value_spin2_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton502_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton501_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton503_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton504_state_changed
                                        (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton502_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton501_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton503_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_setconfig_type001_spinbutton504_value_changed
                                        (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

gboolean
on_ui_window_delete_event              (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
