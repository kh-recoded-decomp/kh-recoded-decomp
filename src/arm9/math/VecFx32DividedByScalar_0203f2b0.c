#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_0204a6ac(VecFx32 *vec, fx32 divisor);

VecFx32 VecFx32DividedByScalar_0203f2b0(const VecFx32 *vec, fx32 divisor)
{
    VecFx32 result = *vec;
    func_0204a6ac(&result, divisor);
    return result;
}
