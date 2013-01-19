/*  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2001-2012
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
 * bsccstruct.h
 *
 * The structure object used in a bscc2sts library.
 */

/*
 * The structure object for conversion tables.
 */
typedef struct {
  char *bscc;
  char *sts;
}ST_BSCC2STS;


/*
 * The structure object for bscc storing.
 */
typedef struct{
  char *p_bscccom;
  char *p_bsccsts;
}ST_BSCCBUF;


/*
 * The structure object for device type conversion.
 */
typedef struct{
  int devno;
  char *type;
}ST_DEVTYPE;


/*
 * The structure object which stores the information used for status conversion.
 */
typedef struct{
  char *p_storetbl;
  int size;
  char *p_bsccsts;
}ST_STORESET;


/*
 * Type declaration for function tables.
 */
typedef int (*FUNCOFEACHMODEL) (ST_STORESET *p_s, bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);
typedef int (*FUNCOFSETPROCESS) (ST_STORESET *p_s, ST_BSCC2STS *p_ct,  bscc2sts_tbl *p_tbl);
typedef int (*FUNCOFMODELSETPROCESS) (ST_STORESET *p_s, ST_BSCC2STS *p_ct,  bscc2sts_tbl *p_tbl, ST_BSCCBUF *p_bsccbuf);


/*
 * The structure object which stores the function corresponding to each model.
 */
typedef struct{
  char prnname[MAXPRINTERNAME+1];
  FUNCOFEACHMODEL model;
}ST_FUNCMODEL;
