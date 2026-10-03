#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void func_ov047_020c6be0(void *target, u32 angle, void *out);

void Camera_StartTargetView_020c1668(void *target, u32 angle, void *out)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        func_ov047_020c6be0(target, angle, out);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
