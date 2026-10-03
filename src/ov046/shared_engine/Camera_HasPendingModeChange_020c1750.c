#include "nitro/types.h"

typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern BOOL func_ov047_020c6b84(void);

BOOL Camera_HasPendingModeChange_020c1750(void)
{
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        return func_ov047_020c6b84();
    case 1:
    case 2:
    case 3:
        break;
    }
    return FALSE;
}
