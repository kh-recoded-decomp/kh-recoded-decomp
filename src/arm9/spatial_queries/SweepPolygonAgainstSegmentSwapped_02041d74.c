#include "nitro/types.h"
#include "nitro/fx_types.h"

void NegateVecFx32_0204aa40(VecFx32 *vec);
BOOL SweepSegmentAgainstPolygon_02048c7c(void *first, void *second, void *contact, u32 flags, const VecFx32 *velocity);

BOOL SweepPolygonAgainstSegmentSwapped_02041d74(void *first, void *second, void *contact, u32 options, const VecFx32 *velocity)
{
    /* Swap shape order and reverse the motion */
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
    return SweepSegmentAgainstPolygon_02048c7c(second, first, contact, flags, &copy);
}


