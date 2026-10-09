#include "nitro/types.h"

typedef void (*WhScanCallback)(void *arg);

typedef struct WirelessScanParameters {
    u8 pad_00[6];
    volatile u16 scanType;
    u8 pad_08[2];
    u16 bssid[3];
} WirelessScanParameters;

typedef struct WirelessHelperState {
    u8 pad_00[2];
    volatile u16 autoConnect;
    u8 pad_04[0xa];
    u16 channel;
    u8 pad_10[0x14];
    u32 sendBufferSize;
    u8 pad_28[4];
    u32 channelIndex;
    u8 pad_30[0xc];
    u32 receiveBufferSize;
    WhScanCallback scanCallback;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern WirelessScanParameters data_ov015_0207ea60;

extern void WH_ChangeSysState(int state);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern BOOL func_ov015_02073e1c(void);

BOOL WH_StartScan(WhScanCallback callback, const u16 *macAddress, u16 channel)
{
    data_ov015_0207e980.receiveBufferSize = 0x180;
    data_ov015_0207e980.sendBufferSize = 0xa0;
    WH_ChangeSysState(2);

    if (macAddress != NULL) {
        data_ov015_0207ea60.bssid[2] = macAddress[2];
        data_ov015_0207ea60.bssid[1] = macAddress[1];
        data_ov015_0207ea60.bssid[0] = macAddress[0];
    } else {
        MI_CpuFill8(data_ov015_0207ea60.bssid, 0xff, sizeof(data_ov015_0207ea60.bssid));
    }

    data_ov015_0207e980.scanCallback = callback;
    data_ov015_0207e980.channelIndex = 0;
    data_ov015_0207e980.channel = channel;
    data_ov015_0207ea60.scanType = 1;
    data_ov015_0207e980.autoConnect = 1;

    if (func_ov015_02073e1c()) {
        return TRUE;
    }
    WH_ChangeSysState(9);
    return FALSE;
}
