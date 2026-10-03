#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x24];
    int sendBufferSize;
    u8 pad_28[0x14];
    int recvBufferSize;
    u8 pad_40[0x10];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u16 data_ov015_0207ec20[];
extern u16 data_ov015_0207eac0[];
extern void SetPanelTransitionMode_020737c4(int state);
extern void WH_SetError_020737d4(int errorCode);
extern void func_ov015_02073b30(void *arg);
extern int WM_StartMP_02011b6c(void (*callback)(void *), u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize,
                               u16 mpFreq);

BOOL StartWirelessMP_02073aa0(void)
{
    int result;

    if (data_ov015_0207e980.sysState == 4 || (u32)data_ov015_0207e980.sysState == 6 || data_ov015_0207e980.sysState == 5) {
        return TRUE;
    }
    SetPanelTransitionMode_020737c4(4);
    result = WM_StartMP_02011b6c(func_ov015_02073b30, data_ov015_0207ec20, (u16)data_ov015_0207e980.recvBufferSize,
                                 data_ov015_0207eac0, (u16)data_ov015_0207e980.sendBufferSize, 1);
    if (result == 2) {
        return TRUE;
    }
    WH_SetError_020737d4(result);
    return FALSE;
}
