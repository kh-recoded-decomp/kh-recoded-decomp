#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern u16 Math_AcosIdx_0202ab20(int cosine);

s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b)
{
    fx32 cosine = VEC_DotProduct_01ff9e6c(a, b);

    if (cosine == FX32_ONE) {
        return 0;
    }
    if (cosine > FX32_ONE) {
        cosine = FX32_ONE;
    } else if (cosine < -FX32_ONE) {
        cosine = -FX32_ONE;
    }
    return Math_AcosIdx_0202ab20(cosine);
}
