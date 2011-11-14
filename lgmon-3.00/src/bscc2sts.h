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
 */

/*
 * bscc2sts.h
 *
 * A header file required to use a bscc2sts library.
 */


/*
 * include necessary Standard headers ...
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


/*
 * macros...
 */
#ifdef _DEBUG
#define INIT  0x2E
#define DEBUG_PRINT(msg) printf msg
#else 
#define INIT  0x20
#define DEBUG_PRINT(msg)
#endif

#define SPACE 0x20
#define CR    0x0A

//Ver.2.70
//#define MAXBSCCCOM     13
//Ver.3.00
#define MAXBSCCCOM     14
#define MAXPRINTERNAME 16
#define MAXDEVTYPE     3

#define HEADER "STS:"
#define OK 0
#define ERR_NOSUPPORTEDMODEL -1  /* The printer which is not assumed. */
#define ERR_MEMORY           -2  /* Allocation of a memory goes wrong. */
#define ERR_PRINTERNAME      -3  /* There are too many input printer names. */
#define ERR_BSCCNON          -4  /* BSCC is not sent. */
#define ERR_BSTNON           -5  /* BST status is not sent. */

#define BST 0
#define DBS 1
#define DJS 2
#define CHD 3
#define CIL 4
//#define LVR 5	// v2.60	The value of HRI is inserted in Lever_position. 
#define HRI 5	// 			Because the display of Lever position was deleted, it substitutes it. 
#define DWS 6
#define DOC 7
#define DSC 8
#define CIR 9
#define CTK 10
#define HCF 11
#define LVR 12	// v2.70	LVR 
#define PDR 13	//Ver.3.00

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
  char reserve[1];
//  char reserve[3];
  char cr;
}bscc2sts_tbl, *Bscc2sts_tbl;

/*
 * prototypes ...
 */
int bscc2sts(char *p_prinname, char *bscc, output_dev *Odev, bscc2sts_tbl *Pr_sts);
