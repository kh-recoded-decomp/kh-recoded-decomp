#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_02053438;
extern BOOL IsVecNear_0204a8f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsNearOrigin_02048ac4(const VecFx32 *point)
{
    return IsVecNear_0204a8f4(point, &data_02053438);
}
