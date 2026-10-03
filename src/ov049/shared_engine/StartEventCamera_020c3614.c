#include "nitro/types.h"

typedef struct EventCameraWork {
    u8 pad000[0x120];
    s32 mode;
    s32 timer;
    u8 pad128[0x64];
    s32 state;
} EventCameraWork;

extern void *EventCamera_Update_020c2d20(EventCameraWork *work);
extern void func_ov049_020c4330(EventCameraWork *work, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void *StartEventCamera_020c3614(EventCameraWork *work, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 mode)
{
    work->mode = mode;
    work->timer = 0;
    work->state = 0;
    func_ov049_020c4330(work, arg1, arg2, arg3, arg4);
    return (void *)EventCamera_Update_020c2d20;
}
