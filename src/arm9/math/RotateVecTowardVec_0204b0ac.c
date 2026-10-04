#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s16 data_0205356c[];

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *v, fx32 scale);
extern void PickPerpendicularAxis_0204acb0(VecFx32 *out, const VecFx32 *v);
extern void func_0204aa68(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800LL) >> 12);
}

static inline VecFx32 CrossVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &result);
    return result;
}

static inline VecFx32 OrthogonalVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_0204aa68(&result, a, b);
    return result;
}

static inline VecFx32 MultAddVec(fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_MultAdd_01ffa09c(scale, a, b, &result);
    return result;
}

void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *target, fx32 angle)
{
    VecFx32 axis;
    fx32 length;
    int index;

    if (angle == 0) {
        return;
    }
    axis = CrossVec(vec, target);
    if (axis.x == 0 && axis.y == 0 && axis.z == 0) {
        VecFx32 perpendicular;
        if (VEC_DotProduct_01ff9e6c(vec, target) >= 0) {
            return;
        }
        PickPerpendicularAxis_0204acb0(&perpendicular, target);
        axis = CrossVec(vec, &perpendicular);
    }
    axis = OrthogonalVec(&axis, vec);
    length = VEC_Mag_01ff9f28(vec);
    index = (int)((((s64)angle << 16) / 0x6488) & 0xffff) >> 4;
    ScaleVecFx32InPlace_0204a5e4(vec, data_0205356c[(0x400 - index) & 0xfff]);
    *vec = MultAddVec(FxMul(data_0205356c[index], length), &axis, vec);
}
