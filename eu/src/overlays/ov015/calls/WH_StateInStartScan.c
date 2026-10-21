#include "nitro/types.h"

typedef struct WMScanExParam {
    void *scanBuf;
    u16 scanBufSize;
    u16 channelList;
    u16 maxChannelTime;
    u8 bssid[6];
    u16 scanType;
    u16 ssidLength;
    u8 ssid[32];
    u16 ssidMatchLength;
    u16 rsv[7];
} WMScanExParam;

typedef struct WirelessHelperState {
    u8 pad_00[0xe];
    u16 channel;
} WirelessHelperState;

/* NitroSDK's MATH_CountLeadingZeros: ARM9 code inlines the CLZ instruction. */
static inline u32 MATH_CountLeadingZeros(u32 x)
{
    asm {
        clz x, x
    }
    return x;
}

static inline u32 MATH_CountTrailingZeros(u32 x)
{
    return 32 - MATH_CountLeadingZeros(~x & (x - 1));
}

extern WirelessHelperState gWhState;
extern WMScanExParam gWhScanExParam;
extern u8 gWirelessScanBuffer[];

extern u16 WM_GetAllowedChannel(void);
extern u16 GetDispersionScanPeriod(void);
extern void WH_SetError(int code);
extern void MI_CpuFill8(void *destination, u8 value, u32 size);
extern int WM_StartScanEx(void (*callback)(void *arg), const WMScanExParam *param);
extern void WH_StateOutStartScanEx(void *arg);

/* Scan the requested channel, or the next allowed one after the last scan, for parents. */
BOOL WH_StateInStartScan(void)
{
    u16 allowed = WM_GetAllowedChannel();
    int result;

    if (allowed == 0x8000) {
        WH_SetError(3);
        return FALSE;
    }
    if (allowed == 0) {
        WH_SetError(0x16);
        return FALSE;
    }

    if (gWhState.channel == 0) {
        u32 channel = MATH_CountTrailingZeros(gWhScanExParam.channelList) + 1;

        do {
            channel++;
            if (channel > 16) {
                channel = 1;
            }
        } while (!(allowed & (1 << (channel - 1))));
        gWhScanExParam.channelList = 1 << (channel - 1);
    } else {
        gWhScanExParam.channelList = 1 << (gWhState.channel - 1);
    }

    gWhScanExParam.maxChannelTime = GetDispersionScanPeriod();
    gWhScanExParam.scanBuf = gWirelessScanBuffer;
    gWhScanExParam.scanBufSize = 0x400;
    gWhScanExParam.scanType = 1;
    gWhScanExParam.ssidLength = 0;
    MI_CpuFill8(gWhScanExParam.ssid, 0xff, sizeof(gWhScanExParam.ssid));

    result = WM_StartScanEx(WH_StateOutStartScanEx, &gWhScanExParam);
    if (result == 2) {
        return TRUE;
    }
    WH_SetError(result);
    return FALSE;
}
