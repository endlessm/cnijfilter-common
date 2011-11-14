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


gboolean SameName(gchar* name1, gchar* name2);
GtkWidget* LookupWidget(GtkWidget* window, const gchar* name);
GtkWidget* GetTopWidget(GtkWidget* widget); 

void UpdateWidgets(GtkWidget* window, gchar* except_name);

void InitSignal();
gboolean EnableSignal();
gboolean DisableSignal();

int GetActiveButtonIndex(GtkWidget* window,
			const gchar* button_name[], int default_index);


int GetTextArrayValueFromCombo(GtkWidget* window, gchar *combo_name,
		const gchar* key_arrya[], const short value_array[]);

void UpdateDrawingArea(GtkWidget* window, const gchar* name);

void DrawPrinterDrawingArea(GtkWidget* window, GtkWidget* area);
void DrawQualityDrawingArea(GtkWidget* window, GtkWidget* area);

/* Ver.2.70 */
void SetPopdownStringsToCombo(GtkWidget *combo, GList *glist, int focus_index);

/* Ver.2.80 */
short SetItemsToComboBox(GtkWidget* window,  gchar *combo_name, short objectid, short currentid );
short ValueToComboIndex( GtkWidget *combo , short object , short target_value ); //nValue -> combo index
/* short NameToComboIndex( GtkWidget *combo , gchar *target_name );*/	/*UI String -> combo index */
void SetTextArrayToComboBox(GtkWidget* window, gchar *combo_name,
		const gchar* key_array[], const short value_array[], short value);
short SetGListToComboBox(GtkWidget* window, gchar *combo_name,
						GList* glist, gchar* current , short objectid);

void UpdateScaleRangeValue(GtkWidget* window, GtkRange* range, gchar* name);
