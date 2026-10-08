#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void GetBoxLocalPoint(const CollisionBox *box, fx32 x, fx32 y, fx32 z, VecFx32 *out)
{
    fx32 scale = box->halfExtents[0] * x;
    VecFx32 point = box->axes[0];
    ScaleVecFx32InPlace(&point, scale);
    *out = point;
    VEC_MultAdd(box->halfExtents[1] * y, &box->axes[1], out, out);
    VEC_MultAdd(box->halfExtents[2] * z, &box->axes[2], out, out);
}
