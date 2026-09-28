#ifndef NITRO_WM_H
#define NITRO_WM_H

#include "nitro/types.h"

struct WMArm7Buf;
struct WMArm9Buf;
struct WMBssDesc;
struct WMCallback;
struct WMGameInfo;
struct WMMPParam;
struct WMMPTmpParam;
struct WMMeasureChannelCallback;
struct WMMeasureChannelReq;
struct WMMpRecvBuf;
struct WMMpRecvData;
struct WMMpRecvHeader;
struct WMParentParam;
struct WMPortRecvCallback;
struct WMPortSendCallback;
struct WMScanParam;
struct WMStartConnectCallback;
struct WMStartConnectReq;
struct WMStartMPCallback;
struct WMStartMPCallbackFull;
struct WMStartMPReq;
struct WMStartParentCallback;
struct WMStartScanCallback;
struct WMStartScanReq;
struct WMStatus;

enum {
    WM_ERRCODE_SUCCESS = 0,
    WM_ERRCODE_FAILED = 1,
    WM_ERRCODE_OPERATING = 2,
    WM_ERRCODE_ILLEGAL_STATE = 3,
    WM_ERRCODE_WM_DISABLE = 4,
    WM_ERRCODE_NO_KEYSET = 5,
    WM_ERRCODE_INVALID_PARAM = 6,
    WM_ERRCODE_NO_CHILD = 7,
    WM_ERRCODE_FIFO_ERROR = 8,
    WM_ERRCODE_TIMEOUT = 9,
    WM_ERRCODE_SEND_QUEUE_FULL = 10,
    WM_ERRCODE_NO_ENTRY = 11,
    WM_ERRCODE_OVER_MAX_ENTRY = 12,
    WM_ERRCODE_INVALID_POLLBITMAP = 13,
    WM_ERRCODE_NO_DATA = 14,
    WM_ERRCODE_SEND_FAILED = 15,
    WM_STATECODE_PARENT_START = 0,
    WM_STATECODE_BEACON_SENT = 2,
    WM_STATECODE_SCAN_START = 3,
    WM_STATECODE_PARENT_NOT_FOUND = 4,
    WM_STATECODE_PARENT_FOUND = 5,
    WM_STATECODE_CONNECT_START = 6,
    WM_STATECODE_CONNECTED = 7,
    WM_STATECODE_BEACON_LOST = 8,
    WM_STATECODE_DISCONNECTED = 9,
    WM_STATECODE_MP_START = 10,
    WM_STATECODE_MPEND_IND = 11,
    WM_STATECODE_MP_IND = 12,
    WM_STATECODE_MPACK_IND = 13,
    WM_STATECODE_PORT_SEND = 20,
    WM_STATECODE_PORT_RECV = 21,
    WM_STATECODE_DISCONNECTED_FROM_MYSELF = 26
};

typedef struct WMGameInfo {
    u16 magicNumber;
    u8 ver;
    u8 platform;
    u32 ggid;
    u16 tgid;
    u8 userGameInfoLength;
    union {
        u8 gameNameCount_attribute;
        u8 attribute;
    };
    u16 parentMaxSize;
    u16 childMaxSize;
    union {
        u16 userGameInfo[112 / sizeof(u16)];
        struct {
            u16 userName[8 / sizeof(u16)];
            u16 gameName[16 / sizeof(u16)];
            u16 padd1[44];
        } old_type;
    };
} WMGameInfo, WMgameInfo;

typedef struct WMStartScanCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6 ];
    u16 channel;
    u16 linkLevel;
    u16 ssidLength;
    u16 ssid[32 / sizeof(u16)];
    u16 gameInfoLength;
    WMGameInfo gameInfo;
} WMStartScanCallback, WMstartScanCallback;

typedef void (*WMCallbackFunc)(void *arg);

#define WM_FIFO_BUF_SIZE        256

#define WM_ARM9WM_BUF_SIZE      512

#define WM_ARM7WM_BUF_SIZE      (256 + 512)

#define WM_STATUS_BUF_SIZE      2048

#define WM_API_REQUEST_ACCEPTED 0x8000

#define WM_NUM_OF_PORT          16

#define WM_NUM_OF_CALLBACK      44

#define WM_BUF_MSG_NUM          10

typedef int WMErrCode;

enum {
    WM_STATE_READY = 0, WM_STATE_STOP, WM_STATE_IDLE, WM_STATE_CLASS1, WM_STATE_TESTMODE,
    WM_STATE_SCAN, WM_STATE_CONNECT, WM_STATE_PARENT, WM_STATE_CHILD, WM_STATE_MP_PARENT,
    WM_STATE_MP_CHILD, WM_STATE_DCF_CHILD, WM_STATE_TESTMODE_RX
};

enum {
    WM_APIID_INITIALIZE = 0, WM_APIID_RESET, WM_APIID_END, WM_APIID_ENABLE, WM_APIID_DISABLE,
    WM_APIID_POWER_ON, WM_APIID_POWER_OFF, WM_APIID_SET_P_PARAM, WM_APIID_START_PARENT,
    WM_APIID_END_PARENT, WM_APIID_START_SCAN, WM_APIID_END_SCAN, WM_APIID_START_CONNECT,
    WM_APIID_DISCONNECT, WM_APIID_START_MP, WM_APIID_SET_MP_DATA, WM_APIID_END_MP,
    WM_APIID_START_DCF, WM_APIID_SET_DCF_DATA, WM_APIID_END_DCF, WM_APIID_SET_WEPKEY,
    WM_APIID_START_KS, WM_APIID_END_KS, WM_APIID_GET_KEYSET, WM_APIID_SET_GAMEINFO,
    WM_APIID_SET_BEACON_IND, WM_APIID_START_TESTMODE, WM_APIID_STOP_TESTMODE,
    WM_APIID_VALARM_MP, WM_APIID_SET_LIFETIME, WM_APIID_MEASURE_CHANNEL,
    WM_APIID_INIT_W_COUNTER, WM_APIID_GET_W_COUNTER, WM_APIID_SET_ENTRY, WM_APIID_AUTO_DEAUTH,
    WM_APIID_SET_MP_PARAMETER, WM_APIID_SET_BEACON_PERIOD, WM_APIID_AUTO_DISCONNECT,
    WM_APIID_START_SCAN_EX, WM_APIID_SET_WEPKEY_EX, WM_APIID_SET_PS_MODE,
    WM_APIID_START_TESTRXMODE, WM_APIID_STOP_TESTRXMODE, WM_APIID_KICK_MP_PARENT,
    WM_APIID_KICK_MP_CHILD, WM_APIID_ASYNC_KIND_MAX,
    WM_APIID_INDICATION = 128, WM_APIID_PORT_SEND, WM_APIID_PORT_RECV, WM_APIID_READ_STATUS
};

typedef int WMApiid;

typedef struct WMParentParam {
    u16 *userGameInfo;
    u16 userGameInfoLength;
    u16 padding;
    u32 ggid;
    u16 tgid;
    u16 entryFlag;
    u16 maxEntry;
    u16 multiBootFlag;
    u16 KS_Flag;
    u16 CS_Flag;
    u16 beaconPeriod;
    u16 rsv1[8];
    u16 rsv2[4];
    u16 channel;
    u16 parentMaxSize;
    u16 childMaxSize;
    u16 rsv[4];
} WMParentParam;

#define WM_PARENT_PARAM_SIZE 64

typedef struct WMBssDesc {
    u16 length;
    u16 rssi;
    u8 bssid[6];
    u16 ssidLength;
    u8 ssid[32];
    u16 capaInfo;
    struct { u16 basic; u16 support; } rateSet;
    u16 beaconPeriod;
    u16 dtimPeriod;
    u16 channel;
    u16 cfpPeriod;
    u16 cfpMaxDuration;
    u16 gameInfoLength;
    u16 otherElementCount;
    u8 gameInfo[128];
} WMBssDesc;

typedef struct WMScanParam {
    WMBssDesc *scanBuf;
    u16 channel;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 rsv[9];
} WMScanParam;

typedef struct WMStartScanReq {
    u16 apiid;
    u16 channel;
    WMBssDesc *scanBuf;
    u16 maxChannelTime;
    u8 bssid[6];
} WMStartScanReq;

typedef struct WMStartConnectReq {
    u16 apiid;
    u16 reserved;
    WMBssDesc *pInfo;
    u8 ssid[24];
    BOOL powerSave;
    u16 reserved2;
    u16 authMode;
} WMStartConnectReq;

typedef struct WMStatus {
    u16 state;
    u16 BusyApiid;
    BOOL apiBusy;
    BOOL scan_continue;
    BOOL mp_flag;
    BOOL dcf_flag;
    BOOL ks_flag;
    BOOL dcf_sendFlag;
    BOOL VSyncFlag;
    u8 wlVersion[8];
    u16 macVersion;
    u16 rfVersion;
    u16 bbpVersion[2];
    u16 mp_parentSize;
    u16 mp_childSize;
    u16 mp_parentMaxSize;
    u16 mp_childMaxSize;
    u16 mp_sendSize;
    u16 mp_recvSize;
    u16 mp_maxSendSize;
    u16 mp_maxRecvSize;
    u8 reserved40[0x72 - 0x40];
    u16 mp_recvBufSize;
    void *mp_recvBuf[2];
    u32 *mp_sendBuf;
    u16 mp_sendBufSize;
    u16 mp_ackTime;
    u16 mp_waitAckFlag;
    u16 mp_readyBitmap;
    u8 reserved88[0x9c - 0x88];
    u16 mp_ignoreSizePrecheckMode;
    u8 reserved9e[0xbc - 0x9e];
    u16 linkLevel;
    u16 minRssi;
    u16 rssiCounter;
    u16 beaconIndicateFlag;
    u16 wepKeyId;
    u16 pwrMgtMode;
    u8 reservedc8[0xe0 - 0xc8];
    u8 MacAddress[6];
    u16 mode;
    WMParentParam pparam;
    u8 childMacAddress[15][6];
    u16 child_bitmap;
    void *pInfoBuf;
    u16 aid;
    u8 parentMacAddress[6];
    u16 scan_channel;
    u8 reserved192[0x800 - 0x192];
} WMStatus;

typedef struct WMArm7Buf {
    WMStatus *status;
    u8 reserved_a[4];
    u32 *fifo7to9;
    u8 reserved_b[0x2f4];
} WMArm7Buf;

typedef struct WMArm9Buf {
    WMArm7Buf *WM7;
    WMStatus *status;
    u32 *indbuf;
    u32 *fifo9to7;
    u32 *fifo7to9;
    u16 dmaNo;
    u16 scanOnlyFlag;
    WMCallbackFunc CallbackTable[WM_NUM_OF_CALLBACK];
    WMCallbackFunc indCallback;
    WMCallbackFunc portCallbackTable[WM_NUM_OF_PORT];
    void *portCallbackArgument[WM_NUM_OF_PORT];
    u32 connectedAidBitmap;
    u16 myAid;
} WMArm9Buf;

typedef struct WMMpRecvBuf {
    u16 rsv1[3];
    u16 length;
    u16 rsv2[1];
    u16 ackTimeStamp;
    u16 timeStamp;
    u16 rate_rssi;
    u16 rsv3[2];
    u16 rsv4[2];
    u8 destAdrs[6];
    u8 srcAdrs[6];
    u16 rsv5[3];
    u16 seqCtrl;
    u16 txop;
    u16 bitmap;
    u16 wmHeader;
    u16 data[2];
} WMMpRecvBuf;

typedef struct WMMpRecvData {
    u16 length;
    u16 rate_rssi;
    u16 aid;
    u16 noResponse;
    u16 wmHeader;
    u16 cdata[1];
} WMMpRecvData;

typedef struct WMMpRecvHeader {
    u16 bitmap;
    u16 errBitmap;
    u16 count;
    u16 length;
    u16 txCount;
    WMMpRecvData data[1];
} WMMpRecvHeader;

#define WMi_CheckState(state) Ov105_WMi_CheckStateEx(1, (state))

#define WM_CHECK_RESULT(res) if ((res) != WM_ERRCODE_SUCCESS) { return (res); }

#define WM_SIZE_MP_DATA_MAX 512

#define WM_SIZE_KS_PARENT_DATA (2 * 16 + 4)

#define WM_SIZE_KS_CHILD_DATA 2

#define WM_SIZE_MP_PARENT_PADDING 6

#define WM_SIZE_MP_CHILD_PADDING 4

#define WM_SIZE_USER_GAMEINFO 112

#define WM_NUM_MAX_CHILD 15

#define WM_SIZE_CHILD_SSID 24

#define WM_SIZE_WEPKEY 80

#define WM_WEPMODE_NO 0

#define WM_MP_TMP_PARAM_MIN_FREQUENCY 0x0001

#define WM_MP_TMP_PARAM_FREQUENCY 0x0002

typedef struct WMMPParam {
    u32 mask;
    u16 minFrequency;
    u16 frequency;
    u16 maxFrequency;
    u16 parentSize;
    u16 childSize;
    u16 parentInterval;
    u16 childInterval;
    u16 parentVCount;
    u16 childVCount;
    u16 defaultRetryCount;
    u8 minPollBmpMode;
    u8 singlePacketMode;
    u8 ignoreFatalErrorMode;
    u8 ignoreSizePrecheckMode;
} WMMPParam;

typedef struct WMMPTmpParam {
    u32 mask;
    u16 minFrequency;
    u16 frequency;
    u16 maxFrequency;
    u16 defaultRetryCount;
    u8 minPollBmpMode;
    u8 singlePacketMode;
    u8 ignoreFatalErrorMode;
    u8 reserved[1];
} WMMPTmpParam;

typedef struct WMStartMPReq {
    u16 apiid;
    u16 rsv1;
    u32 *recvBuf;
    u32 recvBufSize;
    u32 *sendBuf;
    u32 sendBufSize;
    WMMPParam param;
    WMMPTmpParam tmpParam;
} WMStartMPReq;

typedef struct WMMeasureChannelReq {
    u16 apiid;
    u16 ccaMode;
    u16 edThreshold;
    u16 channel;
    u16 measureTime;
} WMMeasureChannelReq;

#define WM_DEFAULT_BEACON_PERIOD 200

#define WM_DEFAULT_SCAN_PERIOD 30

typedef struct WMCallback {
    u16 apiid;
    u16 errcode;
} WMCallback;

typedef struct WMStartParentCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u8 macAddress[6];
    u16 aid;
    u16 reason;
    u8 ssid[24];
    u16 parentSize;
    u16 childSize;
} WMStartParentCallback;

typedef struct WMStartConnectCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 aid;
    u16 reason;
    u16 reserved;
    u8 macAddress[6];
    u16 parentSize;
    u16 childSize;
} WMStartConnectCallback;

typedef struct WMStartMPCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
} WMStartMPCallback;

#define WM_SIZE_SYSTEM_GAMEINFO 16

#define WM_GAMEINFO_MAGIC_NUMBER 0x0001

#define WM_ATTR_FLAG_ENTRY 0x01

#define WM_ATTR_FLAG_MB 0x02

typedef struct WMMeasureChannelCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 channel;
    u16 ccaBusyRatio;
} WMMeasureChannelCallback;

typedef struct WMPortRecvCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 *recvBuf;
    u16 *data;
    u16 length;
    u16 aid;
    u8 macAddress[6];
    u16 seqNo;
    void *arg;
    u16 myAid;
    u16 connectedAidBitmap;
    u8 ssid[24];
    u16 reason;
    u16 reserved;
    u16 maxSendDataSize;
    u16 maxRecvDataSize;
} WMPortRecvCallback;

typedef struct WMPortSendCallback {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 port;
    u16 destBitmap;
    u16 restBitmap;
    u16 sentBitmap;
    u16 reserved;
    u16 *data;
    u16 length;
    u16 seqNo;
    u32 reserved2;
    WMCallbackFunc callback;
    void *arg;
} WMPortSendCallback;

#define WM_ERRCODE_FLASH_ERROR 19

#define WM_SIZE_MACADDR 6

typedef struct WMStartMPCallbackFull {
    u16 apiid;
    u16 errcode;
    u16 state;
    u16 reserved;
    u16 *recvBuf;
} WMStartMPCallbackFull;

#endif
