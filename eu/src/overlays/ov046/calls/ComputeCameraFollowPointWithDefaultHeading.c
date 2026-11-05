#include "nitro/fx_types.h"

extern void Camera_ComputeFollowPoint(void *offsetSource, s32 unused,
                                     const VecFx32 *direction, VecFx32 *out);

void ComputeCameraFollowPointWithDefaultHeading(const VecFx32 *direction, VecFx32 *out)
{
    Camera_ComputeFollowPoint(NULL, 0, direction, out);
}
