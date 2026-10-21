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

extern WirelessHelperState gWhState;
extern WirelessScanParameters gWhScanExParam;

extern void WH_ChangeSysState(int state);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern BOOL WH_StateInStartScan(void);

BOOL WH_StartScan(WhScanCallback callback, const u16 *macAddress, u16 channel)
{
    gWhState.receiveBufferSize = 0x180;
    gWhState.sendBufferSize = 0xa0;
    WH_ChangeSysState(2);

    if (macAddress != NULL) {
        gWhScanExParam.bssid[2] = macAddress[2];
        gWhScanExParam.bssid[1] = macAddress[1];
        gWhScanExParam.bssid[0] = macAddress[0];
    } else {
        MI_CpuFill8(gWhScanExParam.bssid, 0xff, sizeof(gWhScanExParam.bssid));
    }

    gWhState.scanCallback = callback;
    gWhState.channelIndex = 0;
    gWhState.channel = channel;
    gWhScanExParam.scanType = 1;
    gWhState.autoConnect = 1;

    if (WH_StateInStartScan()) {
        return TRUE;
    }
    WH_ChangeSysState(9);
    return FALSE;
}
