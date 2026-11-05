#include "src/collision/VectorTransforms.h"

void CopyVec3WithComponentTransform(VecFx32 *out, const VecFx32 *source,
                                    VectorComponentTransform transform)
{
    VecFx32 temporary = *source;
    TransformVec3Components((u32 *)&temporary, transform);
    *out = temporary;
}
