#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32_0204aa40(VecFx32 *vec);

void NegateVecFx32IfNegative_02040c44(VecFx32 *vec, s32 sign)
{
    if (sign < 0) {
        NegateVecFx32_0204aa40(vec);
    }
}
