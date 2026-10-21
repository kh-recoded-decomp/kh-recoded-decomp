#ifndef KH_RECODED_OV015_WIRELESS_MP_HELPER_H
#define KH_RECODED_OV015_WIRELESS_MP_HELPER_H

#include "nitro/types.h"

/* Only the callback prefix consumed by the MP start handlers is described. */
typedef struct WMStartMPCallback {
    u16 apiId;
    u16 error;
    u16 state;
} WMStartMPCallback;

typedef struct WirelessMPHelper {
    u8 reserved00[0x18];
    void (*connectCallback)(void *argument);
    u8 reserved1c[0x24];
    s32 mode;
    u8 reserved44[0xc];
    s32 systemState;
} WirelessMPHelper;

typedef struct WMDataSharingInfo WMDataSharingInfo;

typedef char WirelessMPCallbackOffsetCheck[
    (u32)&((WirelessMPHelper *)0)->connectCallback == 0x18 ? 1 : -1];
typedef char WirelessMPModeOffsetCheck[
    (u32)&((WirelessMPHelper *)0)->mode == 0x40 ? 1 : -1];
typedef char WirelessMPSystemStateOffsetCheck[
    (u32)&((WirelessMPHelper *)0)->systemState == 0x50 ? 1 : -1];

extern WirelessMPHelper gWhState;
extern WMDataSharingInfo data_ov015_0207fbc0;
extern u32 sWirelessDataSharingDoubleMode;

extern void WH_SetError(s32 error);
extern void WH_ChangeSysState(s32 state);
extern s32 WM_StartDataSharing(WMDataSharingInfo *info, u16 port,
                              u16 aidBitmap, u16 dataLength, BOOL doubleMode);

#endif
