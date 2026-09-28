#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern s32 func_02049d6c(void);

/* Combines a dot product with a scaled fraction. */
u32 ScaleDotProductFraction_0203d658(const VecFx32 *a, s32 scale, const VecFx32 *b) {
    VEC_DotProduct_01ff9e6c(a, b);
    s32 fraction = func_02049d6c();
    s64 product = (s64)fraction * (s64)scale + 0x800;
    return (u32)(product >> 0xc);
}
