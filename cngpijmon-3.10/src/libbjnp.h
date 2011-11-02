#ifndef __LIBBJNP_H__
#define __LIBBJNP_H__

/*
 *  libbjnp.h --- for BJNP lib header
 *
 *  2003.08.05  Start   - BJNP SPEC rev 0.60 support
 *  2003.09.02  Modify  - BJNP SPEC rev 0.73 support
 *  2003.09.30  Modify  - BJNP SPEC rev 0.79 support
 *  2003.10.30  Modify  - Add timeout, retry to each BJNP API.
 *  2003.10.30  Modify  - unchanged parameters are added 'const'.
 *  2003.10.31  Modify  - commentout BJNP_ScanServer().
 */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <sys/sysctl.h>
//
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/sysctl.h>


#define GO_FORWARD(ptr) (ptr = (ptr->next != NULL) ? ptr->next : ptr)



/*
 * BJNP Command ID Definitions (cf. BJNP spec rev 07.3)
 */
#define BJNPCMD_MASK                     0x8000  /* command response mask */

/* REQUEST */
#define kBJNPCMD_REQ_GetVersionInfo      0x0100
#define kBJNPCMD_REQ_GetNicInfo          0x0101
#define kBJNPCMD_REQ_NicCmd              0x0102
#define kBJNPCMD_REQ_SessionStart        0x0110
#define kBJNPCMD_REQ_SessionEnd          0x0111
#define kBJNPCMD_REQ_GetSessionInfo      0x0112
#define kBJNPCMD_REQ_GetTimeout          0x0113
#define kBJNPCMD_REQ_SetTimeout          0x0114
#define kBJNPCMD_REQ_DataRead            0x0120
#define kBJNPCMD_REQ_DataWrite           0x0121
#define kBJNPCMD_REQ_GetDeviceID         0x0130
#define kBJNPCMD_REQ_SoftReset           0x0131

/* RESPONSE */
#define kBJNPCMD_RES_GetVersionInfo      (BJNPCMD_MASK | kBJNPCMD_REQ_GetVersionInfo)
#define kBJNPCMD_RES_GetNicInfo          (BJNPCMD_MASK | kBJNPCMD_REQ_GetNicInfo)
#define kBJNPCMD_RES_NicCmd              (BJNPCMD_MASK | kBJNPCMD_REQ_NicCmd)
#define kBJNPCMD_RES_SessionStart        (BJNPCMD_MASK | kBJNPCMD_REQ_SessionStart)
#define kBJNPCMD_RES_SessionEnd          (BJNPCMD_MASK | kBJNPCMD_REQ_SessionEnd)
#define kBJNPCMD_RES_GetSessionInfo      (BJNPCMD_MASK | kBJNPCMD_REQ_GetSessionInfo)
#define kBJNPCMD_RES_GetTimeout          (BJNPCMD_MASK | kBJNPCMD_REQ_GetTimeout)
#define kBJNPCMD_RES_SetTimeout          (BJNPCMD_MASK | kBJNPCMD_REQ_SetTimeout)
#define kBJNPCMD_RES_DataRead            (BJNPCMD_MASK | kBJNPCMD_REQ_DataRead)
#define kBJNPCMD_RES_DataWrite           (BJNPCMD_MASK | kBJNPCMD_REQ_DataWrite)
#define kBJNPCMD_RES_GetDeviceID         (BJNPCMD_MASK | kBJNPCMD_REQ_GetDeviceID)
#define kBJNPCMD_RES_SoftReset           (BJNPCMD_MASK | kBJNPCMD_REQ_SoftReset)


/*
 * General Result Code
 */

#define BJNP_SUCCESS		 0
#define BJNP_FAILURE		-1

/* argument error */
#define BJNP_ERR_ARG            -100
#define BJNP_ERR_ARG_NULL       (BJNP_ERR_ARG-1)
#define BJNP_ERR_ARG_INVAL      (BJNP_ERR_ARG-2)

/* memory error */
#define BJNP_ERR_MEM            -200
#define BJNP_ERR_MEM_NULL       (BJNP_ERR_MEM-1)
#define BJNP_ERR_MEM_CALLOC     (BJNP_ERR_MEM-2)
#define BJNP_ERR_MEM_MALLOC     (BJNP_ERR_MEM-3)
#define BJNP_ERR_MEM_FREE       (BJNP_ERR_MEM-4)
#define BJNP_ERR_MEM_REALLOC    (BJNP_ERR_MEM-5)
#define BJNP_ERR_MEM_COPY       (BJNP_ERR_MEM-6)
#define BJNP_ERR_MEM_MOVE       (BJNP_ERR_MEM-7)

/* message error */             
#define BJNP_ERR_MSG            -300
#define BJNP_ERR_MSG_CTL        (BJNP_ERR_MSG-1)
#define BJNP_ERR_MSG_GET        (BJNP_ERR_MSG-2)
#define BJNP_ERR_MSG_RCV        (BJNP_ERR_MSG-3)
#define BJNP_ERR_MSG_SND        (BJNP_ERR_MSG-4)

/* semaphore error */
#define BJNP_ERR_SEM            -400
#define BJNP_ERR_SEM_CTL        (BJNP_ERR_SEM-1)
#define BJNP_ERR_SEM_GET        (BJNP_ERR_SEM-2)
#define BJNP_ERR_SEM_OP         (BJNP_ERR_SEM-3)

/* shared memory error */
#define BJNP_ERR_SHM            -500
#define BJNP_ERR_SHM_AT         (BJNP_ERR_SHM-1)
#define BJNP_ERR_SHM_CTL        (BJNP_ERR_SHM-2)
#define BJNP_ERR_SHM_GET        (BJNP_ERR_SHM-3)
#define BJNP_ERR_SHM_DT         (BJNP_ERR_SHM-4)

/* socket error */
#define BJNP_ERR_SKT            -600
#define BJNP_ERR_SKT_SOCKET     (BJNP_ERR_SKT-1)
#define BJNP_ERR_SKT_ACCEPT     (BJNP_ERR_SKT-2)
#define BJNP_ERR_SKT_BIND       (BJNP_ERR_SKT-3)
#define BJNP_ERR_SKT_CONNECT    (BJNP_ERR_SKT-4)
#define BJNP_ERR_SKT_IOCTL      (BJNP_ERR_SKT-5)
#define BJNP_ERR_SKT_LISTEN     (BJNP_ERR_SKT-6)
#define BJNP_ERR_SKT_READ       (BJNP_ERR_SKT-7)
#define BJNP_ERR_SKT_WRITE      (BJNP_ERR_SKT-8)
#define BJNP_ERR_SKT_SOCKOPT    (BJNP_ERR_SKT-9)
#define BJNP_ERR_SKT_TIMEOUT    (BJNP_ERR_SKT-10)

/* file operation ereror */
#define BJNP_ERR_IO             -700
#define BJNP_ERR_IO_FOPEN       (BJNP_ERR_IO-1)
#define BJNP_ERR_IO_FCNTL       (BJNP_ERR_IO-2)
#define BJNP_ERR_IO_UNLINK      (BJNP_ERR_IO-3)

/* process operation ereror */
#define BJNP_ERR_PRC            -800
#define BJNP_ERR_PRC_FORK       (BJNP_ERR_PRC-1)
#define BJNP_ERR_PRC_EXECVE     (BJNP_ERR_PRC-2)
#define BJNP_ERR_PRC_EXEC       (BJNP_ERR_PRC-3)
#define BJNP_ERR_PRC_WAIT       (BJNP_ERR_PRC-4)
#define BJNP_ERR_PRC_SYSTEM     (BJNP_ERR_PRC-5)

#define BJNP_ERR_PROTOCOL            -1000
#define BJNP_ERR_PROTOCOL_COMMAND_ID (BJNP_ERR_PROTOCOL-1)
#define BJNP_ERR_PROTOCOL_PACKET_ID  (BJNP_ERR_PROTOCOL-2)
#define BJNP_ERR_PROTOCOL_SESSION_ID (BJNP_ERR_PROTOCOL-3)

#define BJNP_NO_SESSION		0x00	/* SESSION EXIST FLAG */



/*
 * BJNP Command Result Code (cf. BJNP spec rev 0.73)
 */
#define BJNP_CMDSTAT_SUCCESS                    0x0000
#define BJNP_CMDSTAT_FAIL                       0x8000
#define BJNP_CMDSTAT_NO_DETAIL                  0x8000
#define BJNP_CMDSTAT_NOT_SUPPORTED              0x8100
#define BJNP_CMDSTAT_PARAMETER_ERROR            0x8200
#define BJNP_CMDSTAT_REJECTED                   0x8300
#define BJNP_CMDSTAT_TIMEOUT                    0x8400

#define BJNP_CMDSTAT_COMMAND_SET_DEPENDENT      0x8500
#define BJNP_CMDSTAT_CSD_ALREADY_OPEN           0x8501
#define BJNP_CMDSTAT_CSD_SESSION_BUSY           0x8502

/* General Constants */
#define	BJNP_UDP	  1
#define	BJNP_TCP	  2

#define	BJNP_LIMITED_BCAST   "255.255.255.255"
#define	BJNP_MULTICAST       "224.0.0.1"
#define	BJNP_LINKLOCAL_BCAST "169.254.255.255"


#define	BJNP_LOGPATH               "./BJNPLog"
#define	BJNP_PORT                  "8611"
#define	BJNP_PROTOCOL_ID           0x424A4E50
#define	BJNP_MAX_BUF	           (1024*4)
#define BJNP_RETRY_MAX             3
#define BJNP_UDP_TIMEOUT_SEC       3
#define BJNP_UDP_TIMEOUT_USEC      0
#define BJNP_UDP_TIMEOUT_MSEC      3000
#define BJNP_TCP_TIMEOUT_SEC       30
#define BJNP_TCP_TIMEOUT_USEC      0
#define BJNP_TCP_TIMEOUT_MSEC      30000
#define BJNP_SESSION_START_TIMEOUT 500000  /*usec unit*/

/* Logging Message Switch Constants */
typedef enum {
    BJNP_NONE,
    BJNP_INFO,
    BJNP_MEM,
    BJNP_TRACE,
    BJNP_WARN,
    BJNP_ERROR,
    BJNP_CRITICAL,
    BJNP_ALL,
} bjnp_dvl_t;


/*!
  @brief This structure is common context for all API functions and BJNP applicatiopn.
*/
typedef struct BJNPCntxt
{
    /* BJNP */
    int32_t  protocol_id;       /* Protocol ID */
    int16_t  session_id;        /* Session ID  */
    int16_t  packet_id;         /* Packet ID   */

    /* Socket File Descriptor */
    int usfd;                   /* UDP Socket File Descriptor */
    int tsfd;                   /* TCP Socket File Descriptor */

    /* server (target) network property */
    struct sockaddr_in  sa;
} BJNPCntxt;


/*!
  @brief This structure has NIC information.
  !!! IMPORTANT !!! ---  This version supports only IPv4.
*/
typedef struct BJNPNicInfo
{
    short	  hw_type;
    short	  protocol;
    char	  hw_size;
    char	  ip_size;
    unsigned char hw_addr[6];
    unsigned char ip_addr[4];
} BJNPNicInfo;


/*!
  @brief This structure has a session information.
*/
typedef struct BJNPSessionInfo
{
    uint16_t    session_count;
    uint16_t	tcp_session_id;
    char	computer_name[64];
    char	user_name[64];
    char	document_name[256];
} BJNPSessionInfo;


/*!
  @brief This structure is BJNP server list
*/
typedef struct BJNPServer
{
    int                 id;
    char                nicname[IFNAMSIZ];
    struct sockaddr_in  sa;        /* only IPv4 */

    //struct sockaddr_storage ss;  /* for independent of protocol */

    struct BJNPServer  *next;
} BJNPServer;

/*!
  @brief This structure is packet header.
*/
typedef struct PktHead
{
    union {                    /* PROTOCOl ID         */
        int32_t id;
        char    ch[4];
    } protocol;
    uint16_t    command_id;    /* COMMAND ID          */
    uint16_t    result;        /* COMMAND RESULT CODE */
    uint16_t    packet_id;     /* PACKET ID           */
    uint16_t    session_id;    /* SESSION ID          */
    uint32_t    length;        /* PAYLOAD BYTE SIZE   */
} PktHead;

/*!
  @brief This structure is packet container.
*/
typedef struct PktContainer
{
    PktHead  head;
    void    *data;
} PktContainer;


/*============================================================================ [ Get Version Info ] */
/*!
  @brief This structure is request packet of version information.
*/
typedef struct ReqGetVersionInfoPkt
{
    PktHead	head;
} ReqGetVersionInfoPkt;

/*!
  @brief This structure is response packet of version information.
*/
typedef struct ResGetVersionInfoPkt
{
    PktHead  head;
    char     version_info[4];
} ResGetVersionInfoPkt;


/*============================================================================ [ Get Nic Info ] */
/*!
  @brief This structure is request packet of Nic information.
*/
typedef struct ReqGetNicInfoPkt
{
    PktHead	head;
} ReqGetNicInfoPkt;

/*!
  @brief This structure is response packet of Nic information.
*/
typedef struct ResGetNicInfoPkt
{
    PktHead	head;
    BJNPNicInfo nicinfo;
} ResGetNicInfoPkt;


/*============================================================================ [ Nic Cmd ] */
/*!
  @brief This structure is request packet of Nic command.
*/
typedef struct ReqNicCmdPkt
{
    PktHead	head;
} ReqNicCmdPkt;

/*!
  @brief This structure is response packet of Nic command.
*/
typedef struct ResNicCmdPkt
{
    PktHead	head;
} ResNicCmdPkt;


/*============================================================================ [ Session Start ] */
/*!
  @brief This structure is request packet of session start.
*/
typedef struct ReqSessionStartPkt
{
    PktHead     head;
    uint32_t    retrycount;
    uint32_t    timestamp;
    char        computer_name[64];
    char        user_name[64];
    char        document_name[256];
} ReqSessionStartPkt;

/*!
  @brief This structure is response packet of session start.
*/
typedef struct ResSessionStartPkt
{
    PktHead     head;
    uint32_t    timestamp;
} ResSessionStartPkt;


/*============================================================================ [ Session End ] */
/*!
  @brief This structure is request packet of session end.
*/
typedef struct ReqSessionEndPkt
{
    PktHead	head;
} ReqSessionEndPkt;

/*!
  @brief This structure is response packet of session end.
*/
typedef struct ResSessionEndPkt
{
    PktHead	head;
} ResSessionEndPkt;


/*============================================================================ [ Get Session Info ] */
/*!
  @brief This structure is request packet of getting session information.
*/
typedef struct ReqGetSessionInfoPkt
{
    PktHead	head;
} ReqGetSessionInfoPkt;

/*!
  @brief This structure is response packet of getting session information.
*/
typedef struct ResGetSessionInfoPkt
{
    PktHead           head;
    BJNPSessionInfo   session_info;
} ResGetSessionInfoPkt;


/*============================================================================ [ Get Timeout ] */
/*!
  @brief This structure is request packet of getting timeout value.
*/
typedef struct ReqGetTimeoutPkt
{
    PktHead	head;
} ReqGetTimeoutPkt;

/*!
  @brief This structure is response packet of getting timeout value.
*/
typedef struct ResGetTimeoutPkt
{
    PktHead	head;
    uint32_t    timeout_value;
} ResGetTimeoutPkt;


/*============================================================================ [ Set Timeout ] */
/*!
  @brief This structure is request packet of setting timeout value.
*/
typedef struct ReqSetTimeoutPkt
{
    PktHead	head;
    uint32_t    timeout_value;
} ReqSetTimeoutPkt;

/*!
  @brief This structure is request response of setting timeout value.
*/
typedef struct ResSetTimeoutPkt
{
    PktHead	head;
} ResSetTimeoutPkt;


/*============================================================================ [ Data Read ] */
/*!
  @brief This structure is request packet of reading data from target.
*/
typedef struct ReqDataReadPkt
{
    PktHead     head;
} ReqDataReadPkt;

/*!
  @brief This structure is response packet of reading data from target.
*/
typedef struct ResDataReadPkt
{
    PktHead  head;
    char    *application_data;
} ResDataReadPkt;


/*============================================================================ [ Data Write ] */
/*!
  @brief This structure is request packet of writing data to target.
*/
typedef struct ReqDataWritePkt
{
    PktHead  head;
    char    *application_data;
} ReqDataWritePkt;


/*!
  @brief This structure is response packet of writing data to target.
*/
typedef struct ResDataWritePkt
{
    PktHead	head;
    uint32_t    write_size;
} ResDataWritePkt;


/*============================================================================ [ Get Device ID ] */
/*!
  @brief This structure is request packet of getting device ID from target.
*/
typedef struct ReqGetDeviceIDPkt
{
    PktHead     head;
    uint32_t    timestamp;
} ReqGetDeviceIDPkt;

/*!
  @brief This structure is response packet of getting device ID from target.
*/
typedef struct ResGetDeviceIDPkt
{
    PktHead      head;
    char        *device_id;      /* data size is according with head->length. */
} ResGetDeviceIDPkt;


/*============================================================================ [ Soft Reset ] */
/*!
  @brief This structure is request packet of doing softreset.
*/
typedef struct ReqSoftResetPkt
{
    PktHead     head;
} ReqSoftResetPkt;

/*!
  @brief This structure is response packet of doing softreset.
*/
typedef struct ResSoftResetPkt
{
    PktHead     head;
} ResSoftResetPkt;


//nagatani
// Get_NIC_Info リクエストパケット
typedef struct Get_NIC_Info_request
{
	int32_t	Protocol_ID;	// プロトコルID		(4 bytes) = 'BJNP'
	uint16_t	Command_ID;		// コマンドID		(2 bytes) = 0x0101
	uint16_t	Result;			// コマンドリザルト	(2 bytes) = 0
	uint16_t	Packet_ID;		// パケットID		(2 bytes) = 0
	uint16_t	Session_ID;		// セッションID		(2 bytes) = 0
	uint32_t	Length;			// データ部のレングス	(4 bytes) = 0
} Get_NIC_Info_request;

// Get_NIC_Info レスポンスパケット(IPV4専用)
typedef struct Get_NIC_Info_response
{
	int32_t	Protocol_ID;	// プロトコルID				(4 bytes) 	= 'BJNP'
	uint16_t	Command_ID;		// コマンドID				(2 bytes) 	= 0x8101
	uint16_t	Result;			// コマンドリザルト			(2 bytes) 	= 0
	uint16_t	Packet_ID;		// パケットID				(2 bytes) 	= 0
	uint16_t	Session_ID;		// セッションID				(2 bytes) 	= 0
	uint32_t	Length;			// データ部のレングス			(4 bytes) 	= 16 
	uint16_t	HWTYPE;			// ハードウェタイプ			(2 bytes)	= 0x0001(Ethernet)
	uint16_t	Protocol;		// プロトコルタイプ			(2 bytes)	= 0x0800(IP)
	char	HWAddressSize;	// ハードウェアアドレスサイズ	(1 byte)	= 0x06	(EthernetMACの場合)
	char	IPAddressSize;	// IPアドレスのサイズ			(1 byte)	= 0x04	(IPV4の場合)
	unsigned char	HWAddress[6];	// ハードウェアアドレス		(6 bytes)	= 戻値	(MAC Address)
	unsigned char	IPAddress[4];	// IP Address				(4 bytes)	= 戻値	(IP Address)
	char	dummy[4096];	// 受信時のガード用の余分な領域(実際には不要)
} Get_NIC_Info_response;
//nagatani

/*
 * Packet SIze Definitions (cf. BJNP spec rev 0.73)
 */

/* header regeion */
#define BJNP_PKT_HEAD_SIZE              sizeof( struct PktHead )
/* payload regeion */
#define kBJNPLEN_REQ_GetVersionInfo     (0x0000)
#define kBJNPLEN_RES_GetVersionInfo     (0x0004)
#define kBJNPLEN_REQ_GetNicInfo         (0x0000)
#define kBJNPLEN_RES_GetNicInfo(HW,IP)  (2+2+1+1+HW+IP)
#define kBJNPLEN_REQ_NicCmd(N)          (N)
#define kBJNPLEN_RES_NicCmd(N)          (N)
#define kBJNPLEN_REQ_SessionStart       (0x0188)
#define kBJNPLEN_RES_SessionStart       (0x0004)
#define kBJNPLEN_REQ_SessionEnd         (0x0000)
#define kBJNPLEN_RES_SessionEnd         (0x0000)
#define kBJNPLEN_REQ_GetSessionInfo     (0x0000)
#define kBJNPLEN_RES_GetSessionInfo(N)  (2+(2+64+64+256)*N)
#define kBJNPLEN_REQ_GetTimeout         (0x0000)
#define kBJNPLEN_RES_GetTimeout         (0x0004)
#define kBJNPLEN_REQ_SetTimeout         (0x0004)
#define kBJNPLEN_RES_SetTimeout         (0x0000)
#define kBJNPLEN_REQ_DataRead           (0x0000)
#define kBJNPLEN_RES_DataRead(N)        (N)
#define kBJNPLEN_REQ_DataWrite(N)       (N)
#define kBJNPLEN_RES_DataWrite          (0x0004)
#define kBJNPLEN_REQ_GetDeviceID        (0x0004)
#define kBJNPLEN_RES_GetDeviceID(N)     (N)
#define kBJNPLEN_REQ_SoftReset          (0x0000)
#define kBJNPLEN_RES_SoftReset          (0x0000)


/*
 * Export extern function prototypes
 */

/* Initialize BJNP Lib. */
extern int BJNP_Initialize      ( void );

/* Terminate BJNP Lib. */
extern int BJNP_Terminate       ( void );

/* Open BJNP application context. */
extern int BJNP_Open            ( BJNPCntxt*		ctx,
                                  char*			host,
                                  char*			service,
                                  const unsigned long	protocol_id );

/* Close BJNP application context. */
extern int BJNP_Close           ( BJNPCntxt*     ctx );

/* Set debug verbose level. */
extern int BJNP_SetDebugLevel   ( bjnp_dvl_t     dvl );


/* Get BJNP Server firmware version */
extern int BJNP_GetVersionInfo  ( BJNPCntxt*            ctx,
                                  char*                 verinf,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Get NIC Information of the target(BJNP server). */
extern int BJNP_GetNicInfo      ( BJNPCntxt*            ctx,
                                  BJNPNicInfo*          nicinf,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Do BINP NIC command. */
/*   NOTE: This function is not implemented yet. */

//extern int BJNP_NicCmd        ( BJNPCntxt*            ctx,
//                                char*                 command,
//                                const unsigned int    trns,
//                                const unsigned int    timeout,
//                                const unsigned int    retry );


/* Start BJNP session. */
extern int BJNP_SessionStart    ( BJNPCntxt*            ctx,
                                  const unsigned long   retrycount,
                                  unsigned long*        timestamp,
                                  char*                 computer_name,
                                  char*                 user_name,
                                  char*                 document_name,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Finish BJNP session.  */
extern int BJNP_SessionEnd      ( BJNPCntxt*            ctx,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Get session information. */
extern int BJNP_GetSessionInfo  ( BJNPCntxt*            ctx,
                                  BJNPSessionInfo*      session_info,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Get timeout value. */
extern int BJNP_GetTimeout      ( BJNPCntxt*            ctx,
                                  unsigned long*        session_timeout,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Set timeout value. */
extern int BJNP_SetTimeout      ( BJNPCntxt*            ctx,
                                  const unsigned long   session_timeout,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Read application data. */
extern int BJNP_DataRead        ( BJNPCntxt*            ctx,
                                  char*                 application_data,
                                  unsigned long*        length,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Write application data.*/
extern int BJNP_DataWrite       ( BJNPCntxt*            ctx,
                                  char*                 application_data,
                                  unsigned long*        length,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Get device ID. */
extern int BJNP_GetDeviceID     ( BJNPCntxt*            ctx,
                                  const unsigned long   timestamp,
                                  char*                 device_id,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* Do soft-reset. */
extern int BJNP_SoftReset       ( BJNPCntxt*            ctx,
                                  const unsigned int    trns,
                                  const unsigned int    timeout,
                                  const unsigned int    retry );

/* nagatani */
extern int sendPacket       ( BJNPCntxt *ctx,
							  PktContainer *cntnr,
							  const unsigned int trns);
extern int receivePacket       ( BJNPCntxt *ctx,
							 PktContainer *cntnr, 
							 const unsigned int trns, 
							 const uint32_t timeout );

#endif /*__LIBBJNP_H__*/
