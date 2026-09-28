#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
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
inline void NNSi_G2dSrtcAffineFlagON (NNSG2dSRTControl * pSRT, u16 newFlag)
{
    pSRT->srtData.SRT_EnableFlag |= (u16)newFlag;
}

void NNSi_G2dSrtcSetSRTRotZ_02015614 (NNSG2dSRTControl * pCtrl, u16 rotZ)
{
    if (pCtrl->type == NNS_G2D_SRTCONTROLTYPE_SRT) {
        NNSi_G2dSrtcAffineFlagON(pCtrl, NNS_G2D_AFFINEENABLE_ROTATE);
        pCtrl->srtData.rotZ = rotZ;
    } else {
    }
}
