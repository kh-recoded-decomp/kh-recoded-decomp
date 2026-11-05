#include "src/collision/VectorTransforms.h"

void TransformVec3Components(u32 *values, VectorComponentTransform transform)
{
    u32 value;

    value = transform(values[0]);
    values[0] = value;
    value = transform(values[1]);
    values[1] = value;
    value = transform(values[2]);
    values[2] = value;
}
