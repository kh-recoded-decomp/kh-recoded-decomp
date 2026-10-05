#include "nitro/types.h"

typedef struct FollowControl {
    u8 pad_00[0x14];
    s32 height;
    u8 pad_18[0x9c - 0x18];
    s32 targetHeight;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0x13c];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;

BOOL Camera_IsFollowHeightChanging(void)
{
    FollowControl *follow = (FollowControl *)data_ov046_020c3500->controllerData;

    if (follow->height != follow->targetHeight) {
        return TRUE;
    }
    return FALSE;
}
