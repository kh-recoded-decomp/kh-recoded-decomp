#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/spi.h"
#include "nitro/rtc.h"
#include "nitro/wm.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

u32 PM_SetBackLightAsync(PMLCDTarget target, PMBackLightSwitch sw, PMCallback callback, void * arg);
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
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
void PMi_WaitBusy(void);
void PMi_DummyCallback(u32 result, void * arg);
extern void PMi_WaitBusy (void);
extern void PMi_DummyCallback (u32 result, void * arg);
extern u32 PM_SetBackLightAsync (PMLCDTarget target, PMBackLightSwitch sw, PMCallback callback, void * arg);

u32 PM_SetBackLight_02010518 (PMLCDTarget target, PMBackLightSwitch sw)
{
    u32 commandResult;
    u32 sendResult = PM_SetBackLightAsync(target, sw, PMi_DummyCallback, &commandResult);

    if (sendResult == PM_SUCCESS) {
        PMi_WaitBusy();
        return commandResult;
    }

    return sendResult;
}
