#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_0204a5e4(VecFx32 *vec, fx32 scale);

VecFx32 VecFx32ScaledCopy_0203f4fc(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;
    func_0204a5e4(&result, scale);
    return result;
}
