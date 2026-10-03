#include "nitro/types.h"

typedef struct WMCallback {
    u16 apiid;
    u16 errcode;
} WMCallback;

typedef struct WirelessHelper {
    u8 pad_00[0x34];
    void *parentKeyGenerator;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void WH_SetError_020737d4(int code);
extern void SetPanelTransitionMode_020737c4(u32 mode);
extern BOOL func_ov015_02073894(void);
extern BOOL WH_StartScanStep_02073930(void);

void WH_StateOutSetParentParam_02073830(WMCallback *cb)
{
    if (cb->errcode != 0) {
        WH_SetError_020737d4(cb->errcode);
        SetPanelTransitionMode_020737c4(9);
        return;
    }
    if (data_ov015_0207e980.parentKeyGenerator != NULL) {
        if (!func_ov015_02073894()) {
            SetPanelTransitionMode_020737c4(9);
        }
    } else {
        if (!WH_StartScanStep_02073930()) {
            SetPanelTransitionMode_020737c4(9);
        }
    }
}
