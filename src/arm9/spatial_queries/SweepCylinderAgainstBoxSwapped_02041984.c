#include "nitro/types.h"
#include "nitro/fx_types.h"

void NegateVecFx32_0204aa40(VecFx32 *vec);
BOOL SweepBoxAgainstCylinder_020434d0(void *first, void *second, void *contact, u32 flags, const VecFx32 *velocity);

BOOL SweepCylinderAgainstBoxSwapped_02041984(void *first, void *second, void *contact, u32 options, const VecFx32 *velocity)
{
    u32 flags = (options & 1) ^ 1;
    VecFx32 copy;
    VecFx32 reversed;

    if (options & 4)
        flags |= 8;
    if (options & 8)
        flags |= 4;
    reversed = *velocity;
    NegateVecFx32_0204aa40(&reversed);
    copy = reversed;
    return SweepBoxAgainstCylinder_020434d0(second, first, contact, flags, &copy);
}
