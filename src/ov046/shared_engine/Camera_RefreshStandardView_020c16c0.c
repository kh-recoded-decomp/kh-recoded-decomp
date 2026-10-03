#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void func_ov047_020c6d24(void);

void Camera_RefreshStandardView_020c16c0(void)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        func_ov047_020c6d24();
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
