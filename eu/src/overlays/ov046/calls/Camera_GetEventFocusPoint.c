#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventCameraWork {
    u8 pad_00[0x34];
    int pathKind;
    u8 pad_38[0x114];
    VecFx32 translation;
} EventCameraWork;

extern s32 Camera_GetModeValue(void);
extern EventCameraWork *Camera_GetEventWork(void);
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

void Camera_GetEventFocusPoint(VecFx32 *out)
{
    VecFx32 pathFocus;
    VecFx32 playerFocus;
    EventCameraWork *work;
    VecFx32 *position;

    if (Camera_GetModeValue() == 2) {
        work = Camera_GetEventWork();
        if (work->pathKind == 2) {
            pathFocus.x = work->translation.x;
            pathFocus.y = work->translation.y + 0x14cd;
            pathFocus.z = work->translation.z;
            *out = pathFocus;
            return;
        }
    }
    position = func_ov001_0206dc4c(0);
    playerFocus.x = position->x;
    playerFocus.y = position->y + 0x14cd;
    playerFocus.z = position->z;
    *out = playerFocus;
}
