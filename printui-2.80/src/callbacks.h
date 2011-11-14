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
on_monitor_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_basic_draw_area_expose_event        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_print_bw_button_clicked             (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_quality_draw_area_expose_event      (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_quality_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_button_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_version_dlg_ok_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_version_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_quality_dialog_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_quality_dialog_ok_button_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_quality_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_quality_dialog_help_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_ok_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_default_button_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_help_button_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_gamma_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_color_dialog_vivid_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_color_sample_draw_area_expose_event (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);


gboolean
on_version_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_quality_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_color_dialog_delete_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);


void
on_quality_dialog_ht_button_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_quality_dialog_quality_i_button_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_user_size_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_user_size_ok_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_user_size_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);


void
on_user_size_scale_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_mediatype_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);


void
on_mediatype_dialog_ok_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_mediatype_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

//-------------------------------------------------------------
// Utilities
//-------------------------------------------------------------

void
on_special_dialog_destroy              (GtkObject       *object,
                                        gpointer         user_data);

void
on_special_send_button_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_special_cancel_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_special_std_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_special_dialog_delete_event         (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_regi_dialog_destroy                 (GtkObject       *object,
                                        gpointer         user_data);

gboolean on_regi_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

#if 0
gboolean
on_regi_pixmap1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
#endif

void
on_regi_spinbutton_changed             (GtkSpinButton    *spinbutton,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event      (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_regi_ok_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_regi_drawingarea_expose_event		(GtkWidget		*widget,
								GdkEventExpose	*event,
								gpointer		user_data);

gboolean
on_regi_drawingarea_button_press_event	(GtkWidget		*widget,
								GdkEventButton	*event,
								gpointer		user_data);

void
on_autopower_dialog_destroy            (GtkObject       *object,
                                        gpointer         user_data);

void
on_autopower_send_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_autopower_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_cleaning_dialog_destroy             (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_cleaning_dialog_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_cleaning_radiobutton_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cleaning_execute_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_cleaning_cancel_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_autopower_dialog_destroy            (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_autopower_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_autopower_send_button_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_autopower_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_cleaning_radiobutton_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_cleaning_execute_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_cleaning_cancel_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);

void
on_centering_button_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_borderless_button_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_border_ext_i_button_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_reverse_order_button_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_collate_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_default_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_setup_default_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_ink_warning_dialog_delete_event     (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_ink_warning_dialog_destroy          (GtkObject       *object,
                                        gpointer         user_data);

void
on_ink_warning_send_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_warning_cancel_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_warning_std_button_clicked      (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_ink_reset_dialog_delete_event       (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_ink_reset_dialog_destroy            (GtkObject       *object,
                                        gpointer         user_data);

void
on_ink_reset_execute_button_clicked    (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_reset_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_reset_button_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_ink_reset_button_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_paper_gap_entry_changed             (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_refreshing_dialog_delete_event      (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_refreshing_dialog_destroy           (GtkObject       *object,
                                        gpointer         user_data);

void
on_refreshing_radiobutton_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_refreshing_execute_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);


void
on_regi_cancel_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_combo_button_event(GtkWidget* widget,
							 GdkEvent* event,
							 gpointer user_data);


void
on_cleaning_dialog_destroy             (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_cleaning_dialog_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_pattern_check_dialog_destroy        (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_pattern_check_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_pattern_check_exit_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_pattern_check_cleaning_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_nozzle_check_dialog_destroy         (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_nozzle_check_dialog_delete_event    (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_nozzle_check_execute_button_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_nozzle_check_cancel_button_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_head_alignment_dialog_destroy       (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_head_alignment_dialog_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_head_alignment_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_head_alignment_check_setting_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_head_alignment_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_plate_cleaning_dialog_destroy       (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_plate_cleaning_dialog_delete_event  (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_plate_cleaning_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_plate_cleaning_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_plate_clean_button_clicked     (GtkButton       *button,
                                        gpointer         user_data);


void
on_deep_cleaning_execute_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_deep_cleaning_cancel_button_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_plate_deep_cleaning_dialog_destroy  (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_deep_cleaning_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);
gboolean
on_drylevel_dialog_delete_event   (GtkWidget *widget, 
								   GdkEvent *event, 
								   gpointer user_data);

void 
on_drylevel_dialog_destroy   (GtkObject *object, 
							  gpointer user_data);

void 
on_drylevel_send_button_clicked    (GtkButton *button, 
								    gpointer user_data);

void 
on_drylevel_cancel_button_clicked    (GtkButton *button, 
									  gpointer user_data);

void 
on_drylevel_std_button_clicked    (GtkButton *button, 
								   gpointer user_data);

void 
on_quiet_dialog_destroy    (GtkObject *object, 
							gpointer user_data);

gboolean
on_quiet_dialog_delete_event    (GtkWidget *widget, 
								 GdkEvent *event, 
								 gpointer user_data);

void 
on_quiet_send_button_clicked    (GtkButton *button, 
								 gpointer user_data);

void 
on_quiet_cancel_button_clicked    (GtkButton *button, 
								   gpointer user_data);

void 
on_quiet_std_button_clicked    (GtkButton *button, 
								gpointer user_data);

gboolean
on_mediaborder_dialog_delete_event     (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_mediaborder_dialog_ok_button_clicked    (GtkButton       *button,
											gpointer         user_data);

void
on_mediaborder_dialog_cancel_button_clicked    (GtkButton       *button,
												gpointer         user_data);

gboolean
on_pagesize_dialog_delete_event        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_pagesize_dialog_ok_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_pagesize_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_util_ink_cartridge_button_clicked   (GtkButton       *button,
                                        gpointer         user_data);


void
on_auto_duplex_button_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_longside_button_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_shortside_button_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_cartridge_dialog_ok_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_cartridge_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_cartridge_dialog_defaults_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_ink_cartridge_dialog_delete_event   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_ink_cartridge_dialog_destroy        (GtkObject       *object,
                                        gpointer         user_data);

void
on_ui_main_notebook_switch_page        (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        gint             page_num,
                                        gpointer         user_data);

void
on_color_dialog_vivid_button2_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_gamma2_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_color_dialog_ok_button2_clicked     (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_cancel_button2_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_default_button2_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_color_dialog_delete_event2          (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_color_dialog_vivid_button_clicked2  (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_ok_button_clicked2     (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_cancel_button_clicked2 (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_dialog_default_button_clicked2
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_autopower_type2_dialog_destroy      (GtkObject       *object,
                                        gpointer         user_data);

gboolean
on_autopower_type2_dialog_delete_event (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_autopower_type2_send_button_clicked (GtkButton       *button,
                                        gpointer         user_data);

void
on_autopower_type2_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_media_type_combo_changed            (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_media_supply_combo_changed          (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_media_size_combo_changed            (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_printing_type_combo_changed         (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_color_dialog_correct_combo2_changed (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_color_dialog_gamma_combo2_changed   (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_color_dialog_correct_combo_changed  (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_color_dialog_gamma_combo_changed    (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_mediaborder_dialog_combo_changed    (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_cartridge_type_combo_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_paper_gap_combo_changed             (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_mediatype_dialog_combo_changed      (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_color_dialog_magenta_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_yellow_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_cyan_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_density_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_contrast_scale2_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_cyan_scale_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_magenta_scale_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_yellow_scale_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_black_scale_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

void
on_color_dialog_density_scale_value_changed
                                        (GtkRange        *range,
                                        gpointer         user_data);

gboolean
on_mediasize_illegal_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_mediasize_illegal_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_mediasize_illegal_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_mediasize_recommend_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_mediasize_recommend_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_mediasize_recommend_not_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_mediasize_recommend_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_mediasize_illegal_select_dialog_delete_event
                                        (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_mediasize_illegal_select_apply_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_mediasize_illegal_select_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

void
on_ink_cartridge_dialog_combo_changed  (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_drylevel3_radiobutton_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_drylevel5_radiobutton_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_00   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_01   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_02   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);
gboolean
on_regi_spinbutton_focus_in_event_03   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_04   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_05   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_06   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_07   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_08   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_09   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_10   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_regi_spinbutton_focus_in_event_11   (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);



void
on_copies_spin_value_changed           (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_printing_scaling_spin_value_changed (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_00          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_01          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_02          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_03          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_04          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_05          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_06          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_07          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_08          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_09          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_10          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);

void
on_regi_spinbutton_changed_11          (GtkSpinButton   *spinbutton,
                                        gpointer         user_data);


gboolean
on_regi_dialog_delete_event_no_destroy (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

