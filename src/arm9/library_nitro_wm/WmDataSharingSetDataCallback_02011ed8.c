#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);

typedef struct {
    u8 pad_000[0xcc];
    WMCallbackFunc portCallbackTable[16];
    void *portCallbackArgument[16];
} WMArm9Buf;

typedef struct {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 port;
    u16 destBitmap;
    u16 restBitmap;
    u16 sentBitmap;
    u16 rsv;
    const u16 *data;
    u16 length;
    u16 seqNo;
    WMCallbackFunc callback;
    void *arg;
} WMPortSendCallback;

typedef struct {
    u8 pad_000[0x800];
    u16 seqNum[4];
    u16 writeIndex;
    u16 sendIndex;
    u8 pad_80c[0x10];
    u16 state;
} WMDataSharingInfo;

extern WMArm9Buf *WMi_GetSystemWork_0201103c(void);
extern u16 WM_GetAID_02011394(void);
extern void func_02011f68(void *arg);
extern void func_0201202c(void *arg);

void WmDataSharingSetDataCallback_02011ed8(void *arg)
{
    WMArm9Buf *p = WMi_GetSystemWork_0201103c();
    WMPortSendCallback *callback = (WMPortSendCallback *)arg;
    WMDataSharingInfo *dsInfo;
    WMCallbackFunc func;
    u16 aid;

    dsInfo = (WMDataSharingInfo *)p->portCallbackArgument[callback->port];
    func = p->portCallbackTable[callback->port];
    if (func != func_02011f68 && func != func_0201202c) {
        return;
    }
    if (dsInfo == NULL || dsInfo != callback->arg) {
        return;
    }

    aid = WM_GetAID_02011394();

    if (callback->errcode == 0) {
        if (aid == 0) {
            dsInfo->seqNum[dsInfo->sendIndex] = (u16)(callback->seqNo >> 1);
            dsInfo->sendIndex = (u16)((dsInfo->sendIndex + 1) % 4U);
        }
    } else if (callback->errcode == 10) {
        if (aid != 0) {
            dsInfo->sendIndex = (u16)((dsInfo->sendIndex + 4 - 1) % 4U);
        }
        dsInfo->state = 4;
    } else {
        dsInfo->state = 5;
    }
}
