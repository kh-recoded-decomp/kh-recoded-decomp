#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 fov;
} CameraView;

typedef struct CameraSnapshot {
    VecFx32 position;
    VecFx32 direction;
    u8 pad_18[8];
    s32 followPreset;
    fx32 blendScale;
    fx32 blendSpeed;
    s32 state;
} CameraSnapshot;

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0xe0 - 0x50];
    u32 optionFlags;
    s32 followPreset;
    s32 prevPreset;
    u8 pad_ec[4];
    u32 state;
    u8 pad_f4[0x12c - 0xf4];
    fx32 blendScale;
    fx32 blendSpeed;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void Camera_BlendToVelocityAim_020c132c(const VecFx32 *velocity, s32 curveType, fx32 duration);

void Camera_RestoreSnapshot_020c0e38(const CameraSnapshot *snapshot)
{
    CameraView view;
    VecFx32 direction;
    VecFx32 normalized;
    VecFx32 diff;
    VecFx32 dirCopy;
    VecFx32 up;

    if (snapshot->state == 0) {
        VEC_Subtract_01ff9e3c(&g_cameraManager_020c34e0->target, &g_cameraManager_020c34e0->eye, &diff);
        dirCopy = diff;
        func_01ff9f88(&dirCopy, &normalized);
        direction = normalized;
        Camera_BlendToVelocityAim_020c132c(&direction, 0, 0);
        return;
    }
    view.position = snapshot->position;
    view.direction = snapshot->direction;
    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    view.up = up;
    view.fov = 0x1e000;
    g_cameraManager_020c34e0->followPreset = snapshot->followPreset;
    g_cameraManager_020c34e0->prevPreset = snapshot->followPreset;
    g_cameraManager_020c34e0->blendScale = snapshot->blendScale;
    g_cameraManager_020c34e0->blendSpeed = snapshot->blendSpeed;
    if (g_cameraManager_020c34e0->followPreset == 0x17) {
        g_cameraManager_020c34e0->followPreset = g_cameraManager_020c34e0->prevPreset = 0;
    }
    g_cameraManager_020c34e0->state = snapshot->state;
    if (g_cameraManager_020c34e0->optionFlags & 1) {
        g_cameraManager_020c34e0->state |= 0x10000000;
    } else {
        g_cameraManager_020c34e0->state &= ~0x10000000;
    }
    Camera_BlendToVelocityAim_020c132c(&view.direction, 0, 0);
}


