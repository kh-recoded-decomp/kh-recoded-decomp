#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ComputeCrossProduct_02040500(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void func_0203f580(VecFx32 *out, const VecFx32 *src);

void NormalizeCrossProduct_020404c8(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 normalized;
    VecFx32 cross;

    ComputeCrossProduct_02040500(&cross, a, b);
    func_0203f580(&normalized, &cross);
    *out = normalized;
}
