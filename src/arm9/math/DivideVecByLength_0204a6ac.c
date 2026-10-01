#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 FX_DivFx64c_01ff9c94(fx32 numer, fx32 denom);

void DivideVecByLength_0204a6ac(VecFx32 *vec, fx32 length)
{
    s64 inverse = FX_DivFx64c_01ff9c94(0x1000, length);

    vec->x = (fx32)((vec->x * inverse) >> 32);
    vec->y = (fx32)((vec->y * inverse) >> 32);
    vec->z = (fx32)((vec->z * inverse) >> 32);
}
