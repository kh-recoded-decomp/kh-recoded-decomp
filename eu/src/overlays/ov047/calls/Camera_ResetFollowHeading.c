#include "nitro/types.h"

typedef struct FollowControl {
    u8 pad_00[0x98];
    u32 targetHeading;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0x13c];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern u16 GetBiasAdjustedField(int index);

void Camera_ResetFollowHeading(void)
{
    FollowControl *follow = (FollowControl *)data_ov046_020c3500->controllerData;

    follow->targetHeading = GetBiasAdjustedField(0);
}
