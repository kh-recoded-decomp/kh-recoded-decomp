#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize_01ff9f88(const VecFx32 *source, VecFx32 *dest);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern VecFx32 func_0204bac4(const VecFx32 *source, s32 skipHorizontal);
extern const VecFx32 data_02053438;

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, s32 skipHorizontal)
{
    if (skipHorizontal == 0) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

VecFx32 GetNormalizedAxisRejectionMasked_0204bd6c(const VecFx32 *vec, const VecFx32 *axis, s32 skipHorizontal)
{
    VecFx32 check;
    VecFx32 fallback;
    VecFx32 rejection;
    VecFx32 projected;
    VecFx32 offset;
    VecFx32 result;
    VecFx32 *offsetPtr;
    fx32 dot = VEC_DotProduct_01ff9e6c(vec, axis);

    projected = *axis;
    ScaleVecFx32ComponentsConditional_0204b6c4(&projected, dot, skipHorizontal);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, skipHorizontal);
    check = rejection;
    if (AreVecsWithinRange16_0204a8f4(&check, &data_02053438)) {
        fallback = func_0204bac4(vec, skipHorizontal);
        return fallback;
    }
    VEC_Normalize_01ff9f88(&check, &result);
    return result;
}
