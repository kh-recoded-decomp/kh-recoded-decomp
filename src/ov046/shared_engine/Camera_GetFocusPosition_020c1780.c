#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0xf4];
    VecFx32 *focusTarget;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern VecFx32 *func_ov001_0206dc4c(int playerIndex);

VecFx32 *Camera_GetFocusPosition_020c1780(void)
{
    VecFx32 *focus = g_cameraManager_020c34e0->focusTarget;

    if (focus == NULL) {
        focus = func_ov001_0206dc4c(0);
    }
    return focus;
}
