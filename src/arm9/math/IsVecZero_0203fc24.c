#include "nitro/types.h"
#include "nitro/fx_types.h"

BOOL IsVecZero_0203fc24(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}
