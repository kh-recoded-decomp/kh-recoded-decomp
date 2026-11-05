#include "nitro/types.h"

extern void UpdateOrbitCameraInput(void);
extern void UpdateOrbitCameraFollowPoint(u32 context, u32 data);
extern void StartCameraDrift(u32 context, u32 data);

u32 UpdateOrbitCameraInputFollowAndDrift(u32 context, u32 data)
{
    UpdateOrbitCameraInput();
    UpdateOrbitCameraFollowPoint(context, data);
    StartCameraDrift(context, data);
    return 0;
}
