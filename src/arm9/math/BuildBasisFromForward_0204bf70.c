#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, VecFx32 *basis)
{
    basis[2] = *forward;
    VEC_CrossProduct_01ff9ea8(up, forward, &basis[0]);
    func_01ff9f88(&basis[0], &basis[0]);
    VEC_CrossProduct_01ff9ea8(forward, &basis[0], &basis[1]);
}
