#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
#include "nnsys/g3d.h"

extern void MIi_CpuClearFast_01ff8740(u32 value, void *dest, u32 size);
extern void updateHintVec_01ffe158(u32 *hint, const NNSG3dAnmObj *anmObj);
extern void G3dDrawInternal_01ffdfc8(NNSG3dRS *rs, NNSG3dRenderObj *renderObj);
extern NNSG3dRS *data_0205ab60;
extern u16 data_027e01ec;

void NNS_G3dDraw_01ffe1bc(NNSG3dRenderObj *renderObj) {
    if ((renderObj->flag & 0x10) == 0x10) {
        MIi_CpuClearFast_01ff8740(0, renderObj->hintMatAnmExist, 0x18);
        if (renderObj->anmMat != NULL) {
            updateHintVec_01ffe158(renderObj->hintMatAnmExist, renderObj->anmMat);
        }
        if (renderObj->anmJnt != NULL) {
            updateHintVec_01ffe158(renderObj->hintJntAnmExist, renderObj->anmJnt);
        }
        if (renderObj->anmVis != NULL) {
            updateHintVec_01ffe158(renderObj->hintVisAnmExist, renderObj->anmVis);
        }
        renderObj->flag &= ~0x10;
    }
    if (data_0205ab60 != NULL) {
        G3dDrawInternal_01ffdfc8(data_0205ab60, renderObj);
    } else {
        NNSG3dRS rs;
        data_0205ab60 = &rs;
        G3dDrawInternal_01ffdfc8(&rs, renderObj);
        data_0205ab60 = NULL;
    }
    data_027e01ec = 0;
}
