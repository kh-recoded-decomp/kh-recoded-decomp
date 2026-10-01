#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern VecFx32 func_0204aa68(const VecFx32 *a, const VecFx32 *b);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *axis, s32 angle);

static inline VecFx32 RemoveProjection(const VecFx32 *vec, const VecFx32 *normal, fx32 dot)
{
    VecFx32 projected;
    VecFx32 scaled;
    VecFx32 diff;

    scaled = *normal;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    projected = scaled;
    VEC_Subtract_01ff9e3c(vec, &projected, &diff);
    return diff;
}

static inline VecFx32 MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, v, add, &result);
    return result;
}

static inline VecFx32 Perpendicular(const VecFx32 *a, const VecFx32 *b)
{
    return func_0204aa68(a, b);
}

void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle)
{
    fx32 dot = VEC_DotProduct_01ff9e6c(vec, axis);
    VecFx32 offset = RemoveProjection(vec, axis, dot);
    VecFx32 perpendicular;

    perpendicular = Perpendicular(vec, axis);
    func_0204b0ac(&offset, &perpendicular, angle);
    *vec = MultAdd(dot, axis, &offset);
}
