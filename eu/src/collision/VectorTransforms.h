#ifndef KH_RECODED_VECTOR_TRANSFORMS_H
#define KH_RECODED_VECTOR_TRANSFORMS_H

#include "nitro/fx_types.h"

/* Native quaternion word order is W, X, Y, Z. */
typedef struct QuatFx32 {
    fx32 w, x, y, z;
} QuatFx32;

typedef u32 (*VectorComponentTransform)(u32 value);

void RotateVectorByQuaternion(VecFx32 *dst, const QuatFx32 *quaternion,
                              const VecFx32 *src);
void TransformVec3Components(u32 *values, VectorComponentTransform transform);
void CopyVec3WithComponentTransform(VecFx32 *out, const VecFx32 *source,
                                    VectorComponentTransform transform);

#endif
