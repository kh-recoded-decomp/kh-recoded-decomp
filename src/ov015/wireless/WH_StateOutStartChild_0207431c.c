#include "nitro/types.h"

typedef struct StartConnectCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 aid;
} StartConnectCallback;

typedef struct WirelessHelperState {
    u8 pad_00[0xa];
    u16 myAid;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern void SetPanelTransitionMode_020737c4(int state);
extern void WH_SetError_020737d4(int errorCode);
extern BOOL WH_StateInStartChildMP_020743fc(void);

void WH_StateOutStartChild_0207431c(StartConnectCallback *callback)
{
    if (callback->errcode != 0) {
        WH_SetError_020737d4(callback->errcode);
        if (callback->errcode == 12) {
            SetPanelTransitionMode_020737c4(9);
            return;
        } else if (callback->errcode == 11) {
            SetPanelTransitionMode_020737c4(9);
            return;
        } else if (callback->errcode == 1) {
            SetPanelTransitionMode_020737c4(8);
            return;
        } else {
            SetPanelTransitionMode_020737c4(9);
        }
        return;
    }

    if (callback->state == 8) {
        return;
    }

    if (callback->state == 7) {
        SetPanelTransitionMode_020737c4(4);
        if (!WH_StateInStartChildMP_020743fc()) {
            SetPanelTransitionMode_020737c4(3);
            return;
        }
        data_ov015_0207e980.myAid = callback->aid;
        return;
    } else if (callback->state == 6) {
        return;
    } else if (callback->state == 9) {
        WH_SetError_020737d4(20);
        SetPanelTransitionMode_020737c4(9);
        return;
    } else if (callback->state == 26) {
        return;
    }

    SetPanelTransitionMode_020737c4(9);
}
