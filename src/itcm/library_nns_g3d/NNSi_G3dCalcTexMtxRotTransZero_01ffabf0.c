#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct NNSG3dMatAnmResult {
    u32 flag;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmTexImage;
    u32 prmTexPltt;
    fx32 scaleS;
    fx32 scaleT;
    fx16 sinR;
    fx16 cosR;
    fx32 transS;
    fx32 transT;
    u16 origWidth;
    u16 origHeight;
    fx32 magW;
    fx32 magH;
} NNSG3dMatAnmResult;

extern void FX_DivAsync_01ff9de4(fx32 numer, fx32 denom);
extern fx32 FX_GetDivResult_01ff9d54(void);

void NNSi_G3dCalcTexMtxRotTransZero_01ffabf0(MtxFx44 *m, const NNSG3dMatAnmResult *anm)
{
    fx32 tmpW = anm->origWidth << FX32_SHIFT;
    fx32 tmpH = anm->origHeight << FX32_SHIFT;

    FX_DivAsync_01ff9de4(tmpH, tmpW);
    m->_00 = anm->cosR;
    m->_11 = anm->cosR;
    m->_01 = -anm->sinR * FX_GetDivResult_01ff9d54() >> FX32_SHIFT;
    FX_DivAsync_01ff9de4(tmpW, tmpH);
    m->_30 = (-(anm->sinR + anm->cosR) + FX32_ONE) * anm->origWidth << 3;
    m->_31 = (anm->sinR - anm->cosR + FX32_ONE) * anm->origHeight << 3;
    m->_10 = anm->sinR * FX_GetDivResult_01ff9d54() >> FX32_SHIFT;
}
