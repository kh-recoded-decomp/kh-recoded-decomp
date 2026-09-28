#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void NormalizeVectorOut_0204840c(VecFx32 *dst, const VecFx32 *src)
{
    VecFx32 tmp;
    func_01ff9f88(src, &tmp);
    *dst = tmp;
}
