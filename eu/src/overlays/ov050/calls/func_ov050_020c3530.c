#include "nitro/types.h"

/* Shared engine per-overlay setup sequence. */

extern void UpdatePathCameraCollision(void);
extern void TrackPlayerCameraDirection(u32 context, u32 data);
extern void ClampCameraUpVector(u32 context, u32 data);
extern void StartCameraDriftFromParams(u32 context, u32 data);

u32 func_ov050_020c3530(u32 context, u32 data)
{
    UpdatePathCameraCollision();
    TrackPlayerCameraDirection(context, data);
    ClampCameraUpVector(context, data);
    StartCameraDriftFromParams(context, data);
    return 0;
}
