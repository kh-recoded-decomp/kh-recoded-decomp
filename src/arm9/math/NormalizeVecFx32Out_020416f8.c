#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int func_0204a9b4(VecFx32 *vec);

void NormalizeVecFx32Out_020416f8(VecFx32 *out, const VecFx32 *src)
{
    VecFx32 tmp = *src;
    func_0204a9b4(&tmp);
    *out = tmp;
}
