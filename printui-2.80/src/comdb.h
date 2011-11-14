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


int InitDataBase(char* model_name);
void FreeDataBase();
void InitUserPaperSize();
long GetPaperWidth(short value);
long GetPaperHeight(short value);
int ModelNameToID(char* model_name);
char* GetModelName();
char* GetDispModelName();
gboolean IsAvailableBorderless();
gboolean IsAvailableVivid();
gboolean IsAvailableDuplex();
short GetCurrentPaperGap();
short GetCurrentInkCartridgeSettings();
short GetDefaultExtBorder(int model_id);

int GetValueAndNameArrayTwo(short object_id, short** value, char*** name );


char *ValueToKey(short id, short value);
short KeyToValue(short id, char* name);
char *ValueToName(short id, short value);
short NameToValue(short id, char* name);
gboolean IsAvailableValue(short id, short value);
GList *GetComboList(short ObjectID);
short GetComboNum(short ObjectID);

gchar *GetCurrentString(short ObjectID);
short GetCurrentnValue(short ObjectID);
short GetDefaultnValue(short ObjectID);
short SetTemporaryFlag(short id, short value, short flag);
short GetAllFlags(short id, short value);
int UpdateMenuLink(short id, short value);
void DumpDataBase(int id);
int SetCallbackTableFunc(short id, void (*func)(void *arg), void* func_data);

void my_printui_quit();
