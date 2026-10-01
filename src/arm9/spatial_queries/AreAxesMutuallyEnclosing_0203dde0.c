#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 func_0204aea8(const VecFx32 *vec, const VecFx32 *normal);
extern BOOL IsAxisInsideVectorCone_0203dd00(const VecFx32 *vecA, const VecFx32 *vecB, const VecFx32 *vecC, const VecFx32 *axis);

BOOL AreAxesMutuallyEnclosing_0203dde0(const VecFx32 *axis0, const VecFx32 *axis1, const VecFx32 *axis2, const VecFx32 *axis3)
{
    const VecFx32 *axes[4];
    VecFx32 first;
    VecFx32 second;
    VecFx32 third;
    int i;

    axes[0] = axis0;
    axes[1] = axis1;
    axes[2] = axis2;
    axes[3] = axis3;
    for (i = 0; i < 4; i++) {
        const VecFx32 *axis = axes[i];

        first = func_0204aea8(axes[(i + 1) % 4], axis);
        second = func_0204aea8(axes[(i + 2) % 4], axis);
        third = func_0204aea8(axes[(i + 3) % 4], axis);
        if (!IsAxisInsideVectorCone_0203dd00(&first, &second, &third, axis)) {
            return FALSE;
        }
    }
    return TRUE;
}
