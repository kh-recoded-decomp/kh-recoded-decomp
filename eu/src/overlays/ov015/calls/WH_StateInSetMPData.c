#include "nitro/types.h"

typedef void (*WhSendCallback)(BOOL delivered);
typedef void (*WMCallback)(void *arg);

typedef struct WirelessHelperState {
    u8 pad_00[0x24];
    u32 sendBufferSize;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u16 data_ov015_0207eac0[];

extern void DC_FlushRange(void *address, u32 size);
extern int WM_SetMPDataToPortEx(WMCallback callback, void *arg, const u16 *data, u16 dataSize,
                                u16 destinationBitmap, u16 port, u16 priority);
extern void WH_OnPortSendDone(void *arg);

BOOL WH_StateInSetMPData(void *data, u16 dataSize, WhSendCallback callback)
{
    int result;
    BOOL succeeded;

    DC_FlushRange(data_ov015_0207eac0, data_ov015_0207e980.sendBufferSize);
    result = WM_SetMPDataToPortEx(WH_OnPortSendDone, callback, data, dataSize, 0xffff, 14, 2);
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
