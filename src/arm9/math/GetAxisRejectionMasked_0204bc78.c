#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32ComponentsConditional_0204b6c4(VecFx32 *vec, fx32 scale, s32 skipHorizontal);
extern VecFx32 func_0204bac4(const VecFx32 *axis, s32 skipHorizontal);

static inline void SubtractVecConditional(VecFx32 *vec, const VecFx32 *offset, s32 skipHorizontal)
{
    if (skipHorizontal == 0) {
        vec->x -= offset->x;
        vec->z -= offset->z;
    }
    vec->y -= offset->y;
}

VecFx32 GetAxisRejectionMasked_0204bc78(const VecFx32 *vec, const VecFx32 *axis, s32 skipHorizontal)
{
    VecFx32 check;
    VecFx32 fallback;
    VecFx32 rejection;
    VecFx32 projected;
    VecFx32 offset;
    VecFx32 *offsetPtr;
    fx32 dot = VEC_DotProduct_01ff9e6c(vec, axis);

    projected = *axis;
    ScaleVecFx32ComponentsConditional_0204b6c4(&projected, dot, skipHorizontal);
    offsetPtr = &offset;
    *offsetPtr = projected;
    rejection = *vec;
    SubtractVecConditional(&rejection, offsetPtr, skipHorizontal);
    check = rejection;
    if (check.x != 0 || check.y != 0 || check.z != 0) {
        return rejection;
    }
    fallback = func_0204bac4(axis, skipHorizontal);
    return fallback;
}
