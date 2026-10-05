#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0xf0];
    u32 stateFlags;
    u8 pad_f4[0x13c - 0xf4];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;

u32 Camera_IsFollowFlag13Set(void)
{
    CameraManager *camera = data_ov046_020c3500;

    if (camera->controllerData != NULL) {
        return camera->stateFlags & 0x2000;
    }
    return 0;
}
