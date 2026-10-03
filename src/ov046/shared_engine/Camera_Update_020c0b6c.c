#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x14];
    VecFx32 eye;
    VecFx32 target;
    VecFx32 up;
    u8 pad_38[0x48];
    int type;
    u8 pad_84[0x04];
    int driftState;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern BOOL Camera_IsFrozen_020c0c1c(void);
extern BOOL UpdateDriftParticle_020afb94(int *particle);
extern void Camera_ApplyOffsetClampHeight_020c0a24(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetSoundListenerFrame_0204dc94(const VecFx32 *position, const VecFx32 *forward, const VecFx32 *up);
extern void Camera_CommitView_020c0b34(void *camera);
extern void func_ov047_020c351c(BOOL updateListener);

void Camera_Update_020c0b6c(BOOL updateListener)
{
    CameraManager *camera = g_cameraManager_020c34e0;
    VecFx32 forward;

    if (Camera_IsFrozen_020c0c1c()) {
        return;
    }
    if (g_cameraManager_020c34e0->driftState != 0) {
        UpdateDriftParticle_020afb94(&g_cameraManager_020c34e0->driftState);
    }
    Camera_ApplyOffsetClampHeight_020c0a24();
    if (updateListener) {
        VEC_Subtract_01ff9e3c(&camera->eye, &camera->target, &forward);
        SetSoundListenerFrame_0204dc94(&camera->target, &forward, &camera->up);
    }
    Camera_CommitView_020c0b34(g_cameraManager_020c34e0);
    switch (g_cameraManager_020c34e0->type) {
    case 0:
        func_ov047_020c351c(updateListener);
        break;
    case 1:
    case 2:
    case 3:
        break;
    }
}
