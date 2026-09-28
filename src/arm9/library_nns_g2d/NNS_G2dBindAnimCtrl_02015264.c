#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
#include "nitro/pxi.h"
#include "nitro/spi.h"
#include "nitro/rtc.h"
#include "nitro/wm.h"
#include "nnsys/g2d.h"

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
typedef void (*MBFakeScanCallbackFunc) (u16 type, void * arg);
typedef BOOL (*MBFakeCompareGGIDCallbackFunc) (WMStartScanCallback * arg, u32 defaultGGID);
void NNS_G2dResetAnimCtrlState(NNSG2dAnimController * pAnimCtrl);
extern void NNS_G2dResetAnimCtrlState (NNSG2dAnimController * pAnimCtrl);

void NNS_G2dBindAnimCtrl_02015264 (NNSG2dAnimController * pAnimCtrl, const NNSG2dAnimSequence * pAnimSequence)
{

    pAnimCtrl->pAnimSequence = pAnimSequence;

    NNS_G2dResetAnimCtrlState(pAnimCtrl);
}
