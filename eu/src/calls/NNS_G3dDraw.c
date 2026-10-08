#include "nitro/types.h"
#include "nitro/os_types.h"
#include "nitro/fx_types.h"
#include "nnsys/g3d.h"

typedef struct {
    u8 data[0x188];
} NNSG3dRSEu;

extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void updateHintVec(u32 *hint, const NNSG3dAnmObj *anmObj);
extern void G3dDrawInternal(NNSG3dRS *rs, NNSG3dRenderObj *renderObj);
extern NNSG3dRS *NNS_G3dRS;
extern u16 data_027e01ec;

void NNS_G3dDraw(NNSG3dRenderObj *renderObj) {
    if ((renderObj->flag & 0x10) == 0x10) {
        MIi_CpuClearFast(0, renderObj->hintMatAnmExist, 0x18);
        if (renderObj->anmMat != NULL) {
            updateHintVec(renderObj->hintMatAnmExist, renderObj->anmMat);
        }
        if (renderObj->anmJnt != NULL) {
            updateHintVec(renderObj->hintJntAnmExist, renderObj->anmJnt);
        }
        if (renderObj->anmVis != NULL) {
            updateHintVec(renderObj->hintVisAnmExist, renderObj->anmVis);
        }
        renderObj->flag &= ~0x10;
    }
    if (NNS_G3dRS != NULL) {
        G3dDrawInternal(NNS_G3dRS, renderObj);
    } else {
        NNSG3dRSEu rs;
        NNS_G3dRS = (NNSG3dRS *)&rs;
        G3dDrawInternal((NNSG3dRS *)&rs, renderObj);
        NNS_G3dRS = NULL;
    }
    data_027e01ec = 0;
}
