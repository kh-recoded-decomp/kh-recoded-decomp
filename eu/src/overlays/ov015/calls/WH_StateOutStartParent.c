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

extern WHState gWhState;

extern void WH_SetError(int code);
extern void WH_ChangeSysState(int state);
extern int WM_Disconnect(void *callback, u16 aid);
extern BOOL StartWirelessMP(void);

void WH_StateOutStartParent(WMStartParentCallback *cb) {
    const u16 targetBitmap = (u16)(1 << cb->aid);
    int result;

    if (cb->errcode != 0) {
        WH_SetError(cb->errcode);
        WH_ChangeSysState(9);
        return;
    }
    switch (cb->state) {
    case 7:
        if (gWhState.judgeAccept != NULL && !gWhState.judgeAccept(cb)) {
            result = WM_Disconnect(NULL, cb->aid);
            if (result != 2) {
                WH_SetError(result);
                WH_ChangeSysState(9);
            }
            break;
        }
        gWhState.childBitmap |= targetBitmap;
        if (gWhState.connectCallback != NULL) {
            gWhState.connectCallback(cb);
        }
        break;
    case 9:
        gWhState.childBitmap &= ~targetBitmap;
        if (gWhState.connectCallback != NULL) {
            gWhState.connectCallback(cb);
        }
        break;
    case 0:
        if (!StartWirelessMP()) {
            WH_ChangeSysState(9);
        }
        break;
    case 2:
    case 25:
        break;
    }
}
