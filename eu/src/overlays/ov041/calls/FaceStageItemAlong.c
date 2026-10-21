#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageResources.h"

#define CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : ((x) < (lo) ? (lo) : (x)))

extern const s16 gSinFx12Table[];
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *dest);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 FX_Inv(fx32 value);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u16 Math_AcosIdx(fx32 cosine);
extern u16 Math_AsinIdx(fx32 sine);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *source, VecFx32 *dest);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);

/*
 * Turns an item's model about Y to face along a direction: the angle to its default facing (-Z) gives the
 * cosine, the length of the cross product (signed by its Y) the sine.
 */
void FaceStageItemAlong(StageResourceItem *item, const VecFx32 *direction)
{
    VecFx32 dir;
    VecFx32 forward;
    VecFx32 axis;
    MtxFx33 rotation;
    fx32 cosine;
    fx32 sine;
    u16 angle;
    u16 turn;

    if (VEC_NormalizeLength(direction, &dir) == 0) {
        return;
    }
    forward.x = 0;
    forward.y = 0;
    forward.z = -FX32_ONE;
    cosine = FX_Div(VEC_DotProduct(&forward, &dir), VEC_Mag(&dir));
    cosine = CLAMP(cosine, -FX32_ONE, FX32_ONE);
    angle = Math_AcosIdx(cosine);
    VEC_CrossProduct(&forward, &dir, &axis);
    ScaleVecFx32(FX_Inv(VEC_Mag(&dir)), &axis, &axis);
    sine = VEC_Mag(&axis);
    if (axis.y < 0) {
        sine = FX_Mul(sine, -FX32_ONE);
    }
    sine = CLAMP(sine, -FX32_ONE, FX32_ONE);
    turn = Math_AsinIdx(sine);
    MTX_RotY33_(&rotation, gSinFx12Table[turn >> 4], gSinFx12Table[(0x400 - (angle >> 4)) & 0xfff]);
    item->model.rotation = rotation;
    item->model.flags &= (u16)~STAGE_MODEL_USE_YAW;
}
