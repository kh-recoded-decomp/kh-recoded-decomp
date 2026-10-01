#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 DotFx32Xy_0204a390(const VecFx32 *a, const VecFx32 *b);
extern u16 Math_AcosIdx_0202ab20(int cosine);

u16 AngleBetweenXy_0204a508(const VecFx32 *a, const VecFx32 *b)
{
    fx32 cosine = DotFx32Xy_0204a390(a, b);

    if (cosine > FX32_ONE) {
        cosine = FX32_ONE;
    } else if (cosine < -FX32_ONE) {
        cosine = -FX32_ONE;
    }
    return Math_AcosIdx_0202ab20(cosine);
}
