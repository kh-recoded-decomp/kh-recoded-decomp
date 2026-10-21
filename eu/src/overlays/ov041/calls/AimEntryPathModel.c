#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const s16 gSinFx12Table[];
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern u16 Math_AcosIdx(fx32 cosine);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Inv(fx32 value);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *source, VecFx32 *dest);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u16 Math_AsinIdx(fx32 sine);

/*
 * Aims an entry's path model from start to end (end to start when reverse): the motion keeps both ends, the
 * path heads start - end (end - start), its scale is *scale or that distance, and its facing is the angle
 * between the entry's forward (+Z turned by its yaw) and that direction. Does nothing while the model is idle
 * without an animation.
 */
void AimEntryPathModel(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, BOOL reverse,
                         const fx32 *scale)
{
    VecFx32 forward;
    MtxFx33 rotation;
    VecFx32 axis;
    fx32 cosine;
    fx32 sine;

    if (entry->pathModel->state == 0 && entry->pathModel->animation == -1) {
        return;
    }
    entry->move.motion.start = *start;
    entry->move.motion.end = *end;
    if (reverse) {
        VEC_Subtract(end, start, &entry->pathModel->direction);
    } else {
        VEC_Subtract(start, end, &entry->pathModel->direction);
    }
    if (scale != NULL) {
        entry->pathModel->scale = *scale;
    } else {
        entry->pathModel->scale = VEC_Mag(&entry->pathModel->direction);
    }
    forward.z = FX32_ONE;
    forward.x = 0;
    forward.y = 0;
    MTX_RotY33_(&rotation, gSinFx12Table[entry->slot.node.yaw >> 4],
                gSinFx12Table[(0x400 - (entry->slot.node.yaw >> 4)) & 0xfff]);
    MTX_MultVec33(&forward, &rotation, &forward);
    cosine = FX_Div(VEC_DotProduct(&forward, &entry->pathModel->direction), VEC_Mag(&entry->pathModel->direction));
    if (cosine <= -FX32_ONE) {
        cosine = -FX32_ONE;
    } else if (cosine >= FX32_ONE) {
        cosine = FX32_ONE;
    }
    entry->pathModel->angle = Math_AcosIdx(cosine);
    VEC_CrossProduct(&forward, &entry->pathModel->direction, &axis);
    ScaleVecFx32(FX_Inv(VEC_Mag(&entry->pathModel->direction)), &axis, &axis);
    sine = VEC_Mag(&axis);
    if (axis.y < 0) {
        sine = FX_Mul(sine, -FX32_ONE);
    }
    if (sine <= -FX32_ONE) {
        sine = -FX32_ONE;
    } else if (sine >= FX32_ONE) {
        sine = FX32_ONE;
    }
    entry->pathModel->turn = Math_AsinIdx(sine);
}
