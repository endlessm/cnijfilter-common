/*
 *  Canon Inkjet Printer Driver for Linux
 *  Copyright CANON INC. 2009
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

/* handle */
typedef void* CNNLHANDLE;

/* printer network infomation */
typedef struct _CNNLNICINFO{
	uint8_t		macaddr[6];
	uint8_t		ipaddr[4];
} CNNLNICINFO;

/* Return Code */
#define CNNL_RET_SUCCESS      (0)
#define CNNL_RET_FAILURE      (1)
#define CNNL_RET_BUSY         (2)
#define CNNL_RET_NOT_WORKING  (3)
#define CNNL_RET_POWEROFF     (4)

#define CNNET_SEARCH_BROADCAST	(0)
#define CNNET_SEARCH_UNICAST	(1)
#define CNNET_SEARCH_AUTO		(2)

// for argument "datatype" in CNNL_GetDetailNICInfo
//#define CNNL_TYPE_IPMODE		(0)
//#define CNNL_TYPE_IPADDR		(1)
//#define CNNL_TYPE_MACADDR		(2)
//#define CNNL_TYPE_GATEWAY		(3)
//#define CNNL_TYPE_SUBNETMASK	(4)

// for argument "mode" in CNNL_SetDetailNICInfo
//#define CNNL_IP_DHCP    (0)
//#define CNNL_IP_MANUAL  (1)

//#define CNNL_INTERFACE_USB				(0)
//#define CNNL_INTERFACE_LAN_WIRED		(1)
//#define CNNL_INTERFACE_LAN_WIRELESS		(2)

/* functions */
int CNNL_Init(CNNLHANDLE *h);
int CNNL_Open(CNNLHANDLE h, const char *host);
int CNNL_Close(CNNLHANDLE h);
int CNNL_Terminate(CNNLHANDLE *h);
int CNNL_CheckVersion(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_GetNICInfo(CNNLHANDLE h, char *hwaddr, const int hwsize, char *ipaddr, const int ipsize, const int retry, const uint32_t timeout);
int CNNL_SessionStart(CNNLHANDLE h, const char *user, const char *computer, const char *document, const int retry, const uint32_t timeout);
int CNNL_SessionEnd(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_SetTimeout(CNNLHANDLE h, const uint32_t time, const int retry, const uint32_t timeout);
int CNNL_GetTimeout(CNNLHANDLE h, uint32_t *time, const int retry, const uint32_t timeout);
int CNNL_GetSessionInfo(CNNLHANDLE h, int *count, int *activeid, char *user, const int usersz, char *computer, const int computersz, char *document, const int documentsz, const int retry, const uint32_t timeout);
int CNNL_DataRead(CNNLHANDLE h, void *buf, unsigned long *readsz, const unsigned long bufsz, const int retry, const uint32_t timeout);
int CNNL_DataWrite(CNNLHANDLE h, const void *buf, const uint32_t bufsz, uint32_t *writesize, const int retry, const uint32_t timeout);
int CNNL_GetDeviceID(CNNLHANDLE h, void *buf, unsigned long *readsz, const unsigned long bufsz, const int retry, const uint32_t timeout);
int CNNL_GetModelName(CNNLHANDLE h, char *model, const int modelsz, const int retry, const uint32_t timeout);
// int CNNL_GetDetailNICInfo(CNNLHANDLE h, const int interface, const int datatype, void *data, uint32_t *bufsz, const int retry, const uint32_t timeout);
// int CNNL_SetDetailNICInfo(CNNLHANDLE h, int interface, int mode, const char *ipaddr, const char *subnetmask, const char *gateway, int retry, uint32_t timeout);
int CNNL_SoftReset(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_Abort(CNNLHANDLE h);
int CNNL_StartPrint(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_CheckPrint(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_EndPrint(CNNLHANDLE h, const int retry, const uint32_t timeout);
int CNNL_GetIPAddress(const char *cachefile, const char *macaddr, char *ipaddr, const uint32_t bufsz, int mode, const int retry, const uint32_t timeout);
int CNNL_SearchPrinters(CNNLNICINFO *nic, const char *cachefile, const int maxprinters, int *foundprinters, int mode, const int retry, const uint32_t timeout);
