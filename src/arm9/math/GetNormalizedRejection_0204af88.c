#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ff9f88(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern fx32 NormalizeIfShort_0204a9b4(VecFx32 *vec);
extern VecFx32 func_0204ad4c(const VecFx32 *vec);
extern const VecFx32 data_02053438;

static inline BOOL IsVecNearZero(const VecFx32 *vec, VecFx32 *scratch)
{
    *scratch = *vec;
    return AreVecsWithinRange16_0204a8f4(scratch, &data_02053438);
}

static inline VecFx32 UnitPerpendicular(const VecFx32 *vec)
{
    VecFx32 perpendicular;
    VecFx32 normal;
    perpendicular = func_0204ad4c(vec);
    VEC_Normalize_01ff9f88(&perpendicular, &normal);
    return normal;
}

static inline VecFx32 NormalizedIfShort(VecFx32 vec)
{
    NormalizeIfShort_0204a9b4(&vec);
    return vec;
}

VecFx32 GetNormalizedRejection_0204af88(const VecFx32 *vec, const VecFx32 *axis, fx32 *outDot)
{
    VecFx32 check;
    VecFx32 diff;
    VecFx32 projected;
    VecFx32 subtrahend;
    VecFx32 rejection;
    fx32 dot = VEC_DotProduct_01ff9e6c(vec, axis);

    *outDot = dot;
    projected = *axis;
    ScaleVecFx32InPlace_0204a5e4(&projected, dot);
    subtrahend = projected;
    VEC_Subtract_01ff9e3c(vec, &subtrahend, &diff);
    rejection = diff;
    if (IsVecNearZero(&diff, &check)) {
        return UnitPerpendicular(vec);
    }
    return NormalizedIfShort(rejection);
}
