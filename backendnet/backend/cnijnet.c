/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009-2012
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
 */

//
//  '2004.05.25
//  Using the original "usb.c" code of the CUPS 1.1.14 to create a new
//  backend for writing the printing data into a named pipe.
//

/*
 *
 *   USB port backend for the Common UNIX Printing System (CUPS).
 *
 *   Copyright 1997-2002 by Easy Software Products, all rights reserved.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Easy Software Products and are protected by Federal
 *   copyright law.  Distribution and use rights are outlined in the file
 *   "LICENSE" which should have been included with this file.  If this
 *   file is missing or damaged please contact Easy Software Products
 *   at:
 *
 *       Attn: CUPS Licensing Information
 *       Easy Software Products
 *       44141 Airport View Drive, Suite 204
 *       Hollywood, Maryland 20636-3111 USA
 *
 *       Voice: (301) 373-9603
 *       EMail: cups-info@cups.org
 *         WWW: http://www.cups.org
 *
 * Contents:
 *
 *   main()         - Send a file to the specified USB port.
 *   list_devices() - List all USB devices.
 */

/*
 * Contents are changed(2008.11.17):
 *   main()         - Send a file to the specified Network port.
 *   list_devices() - List Canon network devices.
 */


#include <cups/cups.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#if defined(WIN32) || defined(__EMX__)
#  include <io.h>
#else
#  include <unistd.h>
#  include <fcntl.h>
#  include <termios.h>
#endif /* WIN32 || __EMX__ */

#include "cnijnetlm.h"

/*
 * Local functions...
 */

void	list_devices(void);

/*
 * 'main()' - Send a file to the specified Network port.
 *
 * Usage:
 *
 *    printer-uri job-id user title copies options [file]
 */

int			/* O - Exit status */
main(int  argc,		/* I - Number of command-line arguments (6 or 7) */
     char *argv[])	/* I - Command-line arguments */
{
	char	resource[1024],			/* Resource info (device and options) */
			*options;				/* Pointer to options 				*/
	FILE	*fp;					/* Print file 						*/
	int		copies;					/* Number of copies to print 		*/
	int 	rtn=0;
	
 /*
  * Make sure status messages are not buffered...
  */

	setbuf(stderr, NULL);

	/*
	* Check command-line...
	*/

	if (argc == 1)
	{
		list_devices();
		return (0);
	}
	else if (argc < 6 || argc > 7)
	{
		fputs("Usage: network job-id user title copies options [file]\n", stderr);
		return (1);
	}

	/*
	* If we have 7 arguments, print the file named on the command-line.
	* Otherwise, send stdin instead...
	*/

	if (argc == 6)
	{
		fp     = stdin;
		copies = 1;
	}
	else
	{
		/*
		* Try to open the print file...
		*/

		if ((fp = fopen(argv[6], "rb")) == NULL)
		{
			perror("ERROR: unable to open print file");
			return (1);
		}

		copies = atoi(argv[4]);
	}

	/*
	* Extract the device name and options from the URI...
	*/
/*
 *	httpSeparate(argv[0], method, username, hostname, &port, resource);
 *  This function is deprecated under CUPS 1.2, so we(Canon) do not
 *  use it, instead, parse the argv[0] by ourselves as following.
 */
	if ((strncmp(argv[0], "cnijnet:/", 9) == 0))
	{
		memset(resource, 0, 1024);
		strncpy(resource, argv[0] + 9, 1023);
	}
	else
	{
		perror("ERROR: Illegal backend");
		return (1);
	}

	/*
	* See if there are any options...
	*/

	if ((options = strchr(resource, '?')) != NULL)
	{
		/*
		* Yup, terminate the device name string and move to the first
		* character of the options...
		*/

		*options++ = '\0';
	}

	/*
	* Open the Network port device...
	*/
	
	rtn = _net_canon_bj( argc, CNNET_MODE_PRINT, fp, copies, argv[5], resource, argv[2], argv[3]) ;

	/*
	* Close the socket connection and input file and return...
	*/
	
	if	( fp != stdin )
	fclose( fp ) ;

	// return ( 0 ) ;
	return( rtn ) ;
}

/*
 * 'list_devices()' - List all Canon Network devices.
 */

void
list_devices(void)
{
#ifdef __linux
	_net_canon_bj( 0, CNNET_MODE_SEARCH, NULL, 0, NULL, NULL, NULL, NULL) ;
#endif
}

