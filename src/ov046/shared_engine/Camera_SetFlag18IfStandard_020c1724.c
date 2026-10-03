#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void Camera_SetStateFlag18_020c2a84(BOOL enable);

void Camera_SetFlag18IfStandard_020c1724(BOOL enable)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        Camera_SetStateFlag18_020c2a84(enable);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
