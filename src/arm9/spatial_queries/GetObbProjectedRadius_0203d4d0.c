#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrientedBox {
    VecFx32 center;
    VecFx32 halfExtents;
    VecFx32 axes[3];
    u8 axisAligned : 1;
} OrientedBox;

int abs_0203b430(int x);
void func_0204abf4(VecFx32 *values, int (*transform)(int));
void TransformVectorByBasis_0204bee8(const VecFx32 *vec, const VecFx32 *basis, VecFx32 *out);
fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

fx32 GetObbProjectedRadius_0203d4d0(const OrientedBox *box, const VecFx32 *axis)
{
    VecFx32 localAbs;
    VecFx32 worldAbsCopy;
    VecFx32 worldAbs;
    VecFx32 local;

    if (box->axisAligned) {
        worldAbs = *axis;
        func_0204abf4(&worldAbs, abs_0203b430);
        worldAbsCopy = worldAbs;
        return VEC_DotProduct_01ff9e6c(&worldAbsCopy, &box->halfExtents);
    }
    /* Rotate the axis into box space first */
    TransformVectorByBasis_0204bee8(axis, box->axes, &local);
    localAbs = local;
    func_0204abf4(&localAbs, abs_0203b430);
    return VEC_DotProduct_01ff9e6c(&localAbs, &box->halfExtents);
}
