#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const VecFx32 data_0205344c;
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL AreVecsWithinRange16(const VecFx32 *a, const VecFx32 *b);

BOOL GetCrossIfNonParallel(const VecFx32 *a, const VecFx32 *b, VecFx32 *out)
{
    VecFx32 probe;
    VecFx32 result;
    VecFx32 cross;

    VEC_CrossProduct(a, b, &cross);
    result = cross;
    *(VecFx32 *)&probe = *(VecFx32 *)&cross;
    if (!AreVecsWithinRange16(&probe, &data_0205344c)) {
        *out = result;
        return FALSE;
    }
    return TRUE;
}
