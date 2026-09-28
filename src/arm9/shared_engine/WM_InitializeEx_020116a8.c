#include "nitro/types.h"

typedef struct {
    void *WM7;
    void *status;
    u8 pad_08[8];
    void *fifo7to9;
} WMArm9Buf;

extern int WmInit_02010d64(int wmSysBuf, int dmaNo);
extern void SetCommandArg_02010f28(int idx, int value);
extern void RegisterPxiPreSleepCallback_020113e0(void);
extern int func_0201103c(void);
extern int WMi_SendCommand_02010f80(int id, u16 paramNum, ...);

int WM_InitializeEx_020116a8(int wmSysBuf, int callback, int dmaNo, int miscFlags)
{
    int result;
    WMArm9Buf *wm9buf;

    result = WmInit_02010d64(wmSysBuf, dmaNo);
    if (result != 0) {
        return result;
    }

    SetCommandArg_02010f28(0, callback);
    RegisterPxiPreSleepCallback_020113e0();

    wm9buf = (WMArm9Buf *)func_0201103c();
    result = WMi_SendCommand_02010f80(0, 4, (int)wm9buf->WM7, (int)wm9buf->status, (int)wm9buf->fifo7to9, miscFlags);
    if (result == 0) {
        result = 2;
    }
    return result;
}
