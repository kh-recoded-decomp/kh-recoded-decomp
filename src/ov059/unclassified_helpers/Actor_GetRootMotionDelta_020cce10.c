#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x340];
    fx32 timeScale;
    u8 pad_344[0x7f0 - 0x344];
    u8 animModel[0x958 - 0x7f0];
    fx32 animStep;
} Actor;

extern const s16 g_sinTable_0205356c[];
extern u16 GetLinkedAngleOffset_020cd0e4(Actor *actor);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void AdvanceModelAnimation_020ac9a4(void *model, fx32 step, VecFx32 *out);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

void Actor_GetRootMotionDelta_020cce10(Actor *actor, VecFx32 *out)
{
    MtxFx33 rotation;
    VecFx32 delta;
    int angle = GetLinkedAngleOffset_020cd0e4(actor) >> 4;
    fx32 scale;

    MTX_RotY33_01ff923c(&rotation, -g_sinTable_0205356c[angle], -g_sinTable_0205356c[(0x400 - angle) & 0xfff]);
    AdvanceModelAnimation_020ac9a4(actor->animModel, actor->animStep, &delta);
    scale = FX_Div_01ff9c84(FX32_ONE, actor->timeScale);
    if (scale != FX32_ONE) {
        ScaleVecFx32_01ffafb4(scale, &delta, &delta);
    }
    MTX_MultVec33_01ff9404(&delta, &rotation, out);
}
