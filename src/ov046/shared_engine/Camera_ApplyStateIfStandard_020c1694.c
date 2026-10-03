#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_ApplyViewState_020c6ca4(void *state);

void Camera_ApplyStateIfStandard_020c1694(void *state)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        Camera_ApplyViewState_020c6ca4(state);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
