#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern BOOL func_ov047_020c3538(void);

BOOL Camera_IsViewSettled_020c1540(void)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        return func_ov047_020c3538();
    case 1:
        return TRUE;
    case 2:
        return TRUE;
    case 3:
        break;
    }
    return FALSE;
}
