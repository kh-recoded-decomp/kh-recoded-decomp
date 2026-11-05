#include "src/collision/VectorTransforms.h"
#include "nitro/fx.h"

extern void QuaternionToRotationMatrix(MtxFx33 *matrix, const QuatFx32 *quaternion);
extern void MTX_MultVec33(const VecFx32 *source, const MtxFx33 *matrix, VecFx32 *out);

void RotateVectorByQuaternion(VecFx32 *dst, const QuatFx32 *quaternion,
                              const VecFx32 *src)
{
    MtxFx33 matrix;
    QuaternionToRotationMatrix(&matrix, quaternion);
    MTX_MultVec33(src, &matrix, dst);
}
