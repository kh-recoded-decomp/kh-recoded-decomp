#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ProjectPositionAtTime_0204a7bc(s64 time, const VecFx32 *velocity, const VecFx32 *origin, VecFx32 *out);

VecFx32 ProjectPositionAtTimeMaybeVertical_0204b790(s64 time, const VecFx32 *velocity, const VecFx32 *origin, BOOL verticalOnly)
{
    if (!verticalOnly) {
        VecFx32 full;
        ProjectPositionAtTime_0204a7bc(time, velocity, origin, &full);
        return full;
    } else {
        VecFx32 vertical;
        vertical.x = origin->x;
        vertical.y = (fx32)((origin->y + ((time * velocity->y) >> 12)) >> 20);
        vertical.z = origin->z;
        return vertical;
    }
}
