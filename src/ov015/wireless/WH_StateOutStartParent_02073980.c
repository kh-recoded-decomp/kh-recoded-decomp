#include "nitro/types.h"

typedef struct {
    u16 apiid;
    u16 errcode;
    u8 pad_04[4];
    u16 state;
    u8 pad_0A[6];
    u16 aid;
} WMStartParentCallback;

typedef struct {
    u16 childBitmap;
    u8 pad_02[0x16];
    void (*connectCallback)(void *arg);
    u8 pad_1C[0x14];
    BOOL (*judgeAccept)(WMStartParentCallback *cb);
} WHState;

extern WHState data_ov015_0207e980;

extern void WH_SetError_020737d4(int code);
extern void SetPanelTransitionMode_020737c4(int state);
extern int WM_Disconnect_020119e8(void *callback, u16 aid);
extern BOOL StartWirelessMP_02073aa0(void);

void WH_StateOutStartParent_02073980(WMStartParentCallback *cb) {
    const u16 targetBitmap = (u16)(1 << cb->aid);
    int result;

    if (cb->errcode != 0) {
        WH_SetError_020737d4(cb->errcode);
        SetPanelTransitionMode_020737c4(9);
        return;
    }
    switch (cb->state) {
    case 7:
        if (data_ov015_0207e980.judgeAccept != NULL && !data_ov015_0207e980.judgeAccept(cb)) {
            result = WM_Disconnect_020119e8(NULL, cb->aid);
            if (result != 2) {
                WH_SetError_020737d4(result);
                SetPanelTransitionMode_020737c4(9);
            }
            break;
        }
        data_ov015_0207e980.childBitmap |= targetBitmap;
        if (data_ov015_0207e980.connectCallback != NULL) {
            data_ov015_0207e980.connectCallback(cb);
        }
        break;
    case 9:
        data_ov015_0207e980.childBitmap &= ~targetBitmap;
        if (data_ov015_0207e980.connectCallback != NULL) {
            data_ov015_0207e980.connectCallback(cb);
        }
        break;
    case 0:
        if (!StartWirelessMP_02073aa0()) {
            SetPanelTransitionMode_020737c4(9);
        }
        break;
    case 2:
    case 25:
        break;
    }
}
