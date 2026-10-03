#include "nitro/types.h"

typedef struct FollowControl {
    u8 pad_00[0x98];
    u32 targetHeading;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0x13c];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern u16 GetBiasAdjustedField_0206dc80(int index);

void Camera_ResetFollowHeading_020c464c(void)
{
    FollowControl *follow = (FollowControl *)g_cameraManager_020c34e0->controllerData;

    follow->targetHeading = GetBiasAdjustedField_0206dc80(0);
}
