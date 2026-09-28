#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void CrossProductOut_02048438(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 tmp;
    VEC_CrossProduct_01ff9ea8(a, b, &tmp);
    *dst = tmp;
}
