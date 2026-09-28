#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 row[3];
} Basis3x3;

extern void TransformVectorByBasis_0204bee8(const VecFx32 *vec, const Basis3x3 *basis, VecFx32 *out);

void TransformVectorByBasisOut_020495f8(VecFx32 *dst, const VecFx32 *vec, const Basis3x3 *basis)
{
    VecFx32 tmp;
    TransformVectorByBasis_0204bee8(vec, basis, &tmp);
    *dst = tmp;
}
