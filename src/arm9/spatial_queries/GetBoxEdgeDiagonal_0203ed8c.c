#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void GetBoxEdgeDiagonal_0203ed8c(const CollisionBox *box, s32 axisA, s32 axisB, s32 edge, VecFx32 *out)
{
    /* 0xb50 is one over root two */
    VecFx32 direction = box->axes[axisA];
    ScaleVecFx32InPlace_0204a5e4(&direction, ((edge & 1) ? 1 : -1) * 0xb50);
    *out = direction;
    VEC_MultAdd_01ffa09c(((edge & 2) ? 1 : -1) * 0xb50, &box->axes[axisB], out, out);
}
