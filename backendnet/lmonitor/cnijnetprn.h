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
 *
 * NOTE:
 *  - As a special exception, this program is permissible to link with the
 *    libraries released as the binary modules.
 *  - If you write modifications of your own for these programs, it is your
 *    choice whether to permit this exception to apply to your modifications.
 *    If you do not wish that, delete this exception.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define  READ_BUFFER_SIZE		(1024*1024)

#define  CACHE_PATH       BJLIB_PATH "/cnnet.ini"
#define  CNCL_LIB_PATH    "libcnbpcnclapi%s.so"
#define  CNNL_LIB_LATEST_VERSION			(110)

#define  CNIJNET_SEARCH_MODE_BROADCAST		"broadcast"
#define  CNIJNET_SEARCH_MODE_UNICAST		"unicast"
#define  CNIJNET_SEARCH_MODE_AUTO			"auto"
#define  CNIJNET_SEARCH_MODE_CACHE_ACTIVEONLY	"cacheactive"

/*******************************************************************************
	Definition of time
********************************************************************************/

#define RETRYCOUNT_FIND_PRINTERS (5)
#define WAITTIME_FIND_PRINTERS   (30)
#define WAITTIME_START_SESSION   (5)
#define WAITTIME_RETRY_SEARCH    (30)

#define MAX_COUNT_OF_PRINTERS   (64)
#define STRING_SHORT            (32)
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX            (64)
#endif

#define SESSION_TIMEOUT         (60)

/*******************************************************************************
	Definition of mode
********************************************************************************/

#define CNNL_JOB_PREPARING      (0x0001)
#define CNNL_JOB_WAITING        (0x0002)
#define CNNL_JOB_PRINTING       (0x0003)
#define CNNL_JOB_FINISHING      (0x0004)

#define CNNL_JOB_CANCELLED      (0x1000)
#define CNNL_JOB_ERROR          (0x2000)


typedef int (*CNNL_PRINTCHECK_FUNC)(CNNLHANDLE h, const int retry, const unsigned long timeout);

