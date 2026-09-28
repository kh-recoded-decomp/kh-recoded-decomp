#include "nitro/types.h"
#include "nitro/fx_types.h"

void NegateVecComponentsConditional_0204b758(VecFx32 *vec, s32 sign, s32 skipHorizontal)
{
    if (sign >= 0) {
        return;
    }
    if (skipHorizontal == 0) {
        vec->x = -vec->x;
        vec->z = -vec->z;
    }
    vec->y = -vec->y;
}
