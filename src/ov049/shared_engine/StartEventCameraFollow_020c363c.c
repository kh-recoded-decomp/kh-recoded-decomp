#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventCameraWork {
    u8 pad000[0x120];
    s32 mode;
    s32 timer;
    u8 pad128[0x64];
    s32 state;
    u8 pad190[0xc];
    fx32 distance;
    fx32 targetDistance;
    fx32 baseDistance;
} EventCameraWork;

extern void *EventCamera_Update_020c2d20(EventCameraWork *work);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void func_ov049_020c4510(EventCameraWork *work, VecFx32 *points, s32 arg2, s32 arg3, s32 arg4);

void *StartEventCameraFollow_020c363c(EventCameraWork *work, VecFx32 *points, s32 arg2, s32 arg3, s32 arg4, s32 mode)
{
    fx32 distance;
    work->mode = mode;
    work->timer = 0;
    work->state = 0;
    distance = func_01ffa0f4(&points[0], &points[1]);
    work->targetDistance = distance;
    work->distance = distance;
    work->baseDistance = distance;
    func_ov049_020c4510(work, points, arg2, arg3, arg4);
    return (void *)EventCamera_Update_020c2d20;
}
