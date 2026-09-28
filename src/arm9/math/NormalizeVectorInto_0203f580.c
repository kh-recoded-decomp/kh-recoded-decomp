#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void NormalizeVectorInto_0203f580(VecFx32 *dest, const VecFx32 *src)
{
    VecFx32 tmp;
    func_01ff9f88(src, &tmp);
    *dest = tmp;
}
