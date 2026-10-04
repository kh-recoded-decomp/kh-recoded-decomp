#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *v, fx32 scale);
extern int Math_AcosIdx_0202ab20(fx32 cosine);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle);

static inline void SnapToDirection(VecFx32 *vec, const VecFx32 *dir)
{
    fx32 length = VEC_Mag_01ff9f28(vec);
    VecFx32 result = *dir;
    func_01ffaff4(&result, &result);
    ScaleVecFx32InPlace_0204a5e4(&result, length);
    *vec = result;
}

void TurnVecTowardVecLimited_0204b1fc(VecFx32 *vec, const VecFx32 *target, fx32 maxAngle)
{
    VecFx32 vecDir;
    VecFx32 targetDir;
    VecFx32 vecNorm;
    VecFx32 targetNorm;
    fx32 cosine;
    fx32 angle;

    func_01ff9f88(target, &targetNorm);
    targetDir = targetNorm;
    func_01ff9f88(vec, &vecNorm);
    vecDir = vecNorm;
    cosine = VEC_DotProduct_01ff9e6c(&vecDir, &targetDir);
    if (cosine > 0xfae) {
        SnapToDirection(vec, target);
        return;
    }
    if (cosine > 0x1000) {
        cosine = 0x1000;
    } else if (cosine < -0x1000) {
        cosine = -0x1000;
    }
    angle = ((s64)(s16)Math_AcosIdx_0202ab20(cosine) * 0x6488) / 0x10000;
    if (maxAngle >= angle - 0x20) {
        SnapToDirection(vec, target);
        return;
    }
    RotateVecTowardVec_0204b0ac(vec, target, maxAngle);
}
