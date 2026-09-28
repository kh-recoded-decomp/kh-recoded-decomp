#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void ComputeCrossProduct_02040500(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &result);
    *out = result;
}
