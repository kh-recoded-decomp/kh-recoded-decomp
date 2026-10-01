#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SweepResult SweepResult;

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern BOOL SweepIntervalOnAxis_01fff6c8(fx32 extent, fx32 distance, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime);

BOOL SweepAlongProjectedAxis_020481c4(fx32 extent, const VecFx32 *offset, const VecFx32 *axis, u8 feature, const VecFx32 *velocity, SweepResult *result, s64 *outTime)
{
    return SweepIntervalOnAxis_01fff6c8(extent, VEC_DotProduct_01ff9e6c(axis, offset), axis, feature, velocity, result, outTime);
}
