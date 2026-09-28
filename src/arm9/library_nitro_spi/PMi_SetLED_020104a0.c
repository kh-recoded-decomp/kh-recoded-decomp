#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/mi.h"
#include "nitro/pxi.h"
#include "nitro/spi.h"
#include "nitro/rtc.h"
#include "nitro/snd.h"
#include "nitro/wm.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

u32 PMi_SetLEDAsync(PMLEDStatus status, PMCallback callback, void * arg);
typedef enum WVRResult {
    WVR_RESULT_SUCCESS = 0,
    WVR_RESULT_OPERATING,
    WVR_RESULT_DISABLE,
    WVR_RESULT_INVALID_PARAM,
    WVR_RESULT_FIFO_ERROR,
    WVR_RESULT_ILLEGAL_STATUS,
    WVR_RESULT_VRAM_LOCKED,
    WVR_RESULT_FATAL_ERROR,
    WVR_RESULT_MAX
} WVRResult;
typedef void (*WVRCallbackFunc) (void * arg, WVRResult result);
typedef void (*MBCommPStateCallback) (u16 child_aid, u32 status, void * arg);
typedef void (*MBCommCStateCallbackFunc) (u32 status, void * arg);
typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
void PMi_WaitBusy(void);
void PMi_DummyCallback(u32 result, void * arg);
extern void PMi_WaitBusy (void);
extern void PMi_DummyCallback (u32 result, void * arg);
extern u32 PMi_SetLEDAsync (PMLEDStatus status, PMCallback callback, void * arg);

u32 PMi_SetLED_020104a0 (PMLEDStatus status)
{
    u32 commandResult;
    u32 sendResult = PMi_SetLEDAsync(status, PMi_DummyCallback, &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusy();
        return commandResult;
    }

    return sendResult;
}
