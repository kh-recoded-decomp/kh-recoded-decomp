#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void AddActorVectors_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void AddVecFx32Into_0203f980(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    AddActorVectors_01ff9e0c(a, b, &result);
    *dest = result;
}
