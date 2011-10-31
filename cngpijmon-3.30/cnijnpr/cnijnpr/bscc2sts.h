/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2010
 *  All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License.
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

/*
 * The structure object for device information.
 */
typedef struct {
  int   dev;
  char  status;
  char  recv[3];
}output_dev, *Output_dev;

/*
 * The structure object which stores the changed status.
 */
typedef struct {
  char header[4];
  char dev[4];
  char pr_name[16];
  char base_stat[2];
  char busy_stat;
  char job_stat;
  struct {
	char type;
	char exchange;
  }cartridge[2];
  struct {
	char color;
	char alert;
	char fill[3];
	char resv;
  }ink[8];
  char ink_check;
//Ver.2.70
  char destination;
//  char lever_position;
  char warning[12];
  char operator_call[12];
  char service_call[4];
//Ver.2.70
  char lever_position;
//Ver.3.00
  char prnregion;
//Ver.3.10
  char service_call2;
  char reserve[10];
  char cr;
}bscc2sts_tbl, *Bscc2sts_tbl;

/*
 * prototypes ...
 */
int bscc2sts(char *p_prinname, char *bscc, output_dev *Odev, bscc2sts_tbl *Pr_sts);
