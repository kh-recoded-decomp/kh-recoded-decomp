#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
#include "nitro/pxi.h"
#include "nitro/spi.h"
#include "nitro/rtc.h"
#include "nitro/wm.h"
#include "nnsys/gfd.h"
#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

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
void NNS_G2dBindAnimCtrl(NNSG2dAnimController * pAnimCtrl, const NNSG2dAnimSequence * pAnimSequence);
typedef BOOL (*VramTransferTaskRegisterFuncPtr)(NNS_GFD_DST_TYPE type, u32 dstAddr, void * pSrc, u32 szByte);
extern void func_020897d0 (NNSG2dCellAnimation * pCellAnim);

void NNS_G2dSetCellAnimationSequence_02089834 (NNSG2dCellAnimation * pCellAnim, const NNSG2dAnimSequence * pAnimSeq)
{

    NNS_G2dBindAnimCtrl(&pCellAnim->animCtrl, pAnimSeq);
    func_020897d0(pCellAnim);
}
