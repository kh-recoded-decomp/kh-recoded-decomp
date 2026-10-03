#include "nitro/types.h"

typedef struct WMPortSendCallback {
    u16 apiid;
    u16 errcode;
    u8 pad_04[0x20 - 4];
    void (*pSendCallback)(BOOL delivered);
} WMPortSendCallback;

typedef struct WirelessHelper {
    u8 pad_00[0x18];
    void (*sendHook)(WMPortSendCallback *cb);
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void WH_SetError_020737d4(int code);

void WH_OnPortSendDone_020747e8(WMPortSendCallback *cb)
{
    if (data_ov015_0207e980.sendHook != NULL) {
        data_ov015_0207e980.sendHook(cb);
    }
    if (cb->errcode != 0 && cb->errcode != 15) {
        WH_SetError_020737d4(cb->errcode);
        return;
    }
    if (cb->pSendCallback != NULL) {
        cb->pSendCallback(cb->errcode == 0);
    }
}
