#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

void Vec_DotSelf_02048bac(const VecFx32 *v)
{
    VEC_DotProduct_01ff9e6c(v, v);
}
