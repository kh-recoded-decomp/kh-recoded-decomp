#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_0204ad4c(VecFx32 *out, VecFx32 *v, s32 param3, s32 param4);
extern void NormalizeVectorInto_0203f580(VecFx32 *dest, const VecFx32 *src);

void ComputeNormalizedCrossInto_0203f548(VecFx32 *dest, VecFx32 *v, s32 param3, s32 param4)
{
    VecFx32 normalized;
    VecFx32 raw;
    func_0204ad4c(&raw, v, param3, param4);
    NormalizeVectorInto_0203f580(&normalized, &raw);
    *dest = normalized;
}
