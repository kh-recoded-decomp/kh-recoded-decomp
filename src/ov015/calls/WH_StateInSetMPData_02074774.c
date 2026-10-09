#include "nitro/types.h"

typedef void (*WhSendCallback)(BOOL delivered);
typedef void (*WMCallback)(void *arg);

typedef struct WirelessHelperState {
    u8 pad_00[0x24];
    u32 sendBufferSize;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u16 data_ov015_0207eac0[];

extern void DC_FlushRange_0200344c(void *address, u32 size);
extern int WM_SetMPDataToPortEx_02011ba8(WMCallback callback, void *arg, const u16 *data, u16 dataSize,
                                u16 destinationBitmap, u16 port, u16 priority);
extern void WH_OnPortSendDone_020747e8(void *arg);

BOOL WH_StateInSetMPData_02074774(void *data, u16 dataSize, WhSendCallback callback)
{
    int result;
    BOOL succeeded;

    DC_FlushRange_0200344c(data_ov015_0207eac0, data_ov015_0207e980.sendBufferSize);
    result = WM_SetMPDataToPortEx_02011ba8(WH_OnPortSendDone_020747e8, callback, data, dataSize, 0xffff, 14, 2);
    switch (result) {
    default:
        succeeded = FALSE;
        break;
    case 2:
        succeeded = TRUE;
        break;
    }
    return succeeded;
}
