#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_02053438;
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);

BOOL GetCrossIfNonParallel_0204a9e4(const VecFx32 *a, const VecFx32 *b, VecFx32 *out)
{
    VecFx32 probe;
    VecFx32 result;
    VecFx32 cross;

    VEC_CrossProduct_01ff9ea8(a, b, &cross);
    result = cross;
    *(VecFx32 *)&probe = *(VecFx32 *)&cross;
    if (!AreVecsWithinRange16_0204a8f4(&probe, &data_02053438)) {
        *out = result;
        return FALSE;
    }
    return TRUE;
}
