#include "nitro/types.h"

typedef struct CameraModeState {
    int mode;
    u8 pad_04[0x94];
    int targetHeading;
} CameraModeState;

typedef struct CameraManager {
    u8 pad_00[0xf4];
    int pathActive;
    u8 pad_f8[0x44];
    CameraModeState modeState;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern int func_ov046_020c0d68(void);
extern unsigned int func_ov046_020c2ab8(CameraManager *camera);
extern u16 GetBiasAdjustedField_0206dc80(int playerIndex);

void Camera_RefreshTargetHeading_020c2bac(void)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    camera->pathActive = 0;
    if (func_ov046_020c0d68() == 0) {
        CameraModeState *state = &g_cameraManager_020c34e0->modeState;

        if (!func_ov046_020c2ab8(camera)) {
            state->targetHeading = GetBiasAdjustedField_0206dc80(0);
            return;
        }
        state->targetHeading = 0;
    }
}
