#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 basePosition;
    u8 pad_44[0x3c];
    s32 mode;
    u8 pad_84[0x5c];
    s32 unk_E0;
    s32 unk_E4;
    u8 pad_E8[0x8];
    s32 unk_F0;
    u8 pad_F4[0x38];
    fx32 followDistance;
    s32 unk_130;
} CameraManager;

typedef struct CameraSnapshot {
    VecFx32 position;
    VecFx32 direction;
    s32 mode;
    s32 unk_1C;
    s32 unk_20;
    fx32 followDistance;
    s32 unk_28;
    s32 unk_2C;
} CameraSnapshot;

extern CameraManager *g_cameraManager_020c34e0;
extern void func_ov021_020af9a4(CameraManager *camera, VecFx32 *direction);

void Camera_SaveSnapshot_020c0dd4(CameraSnapshot *snapshot)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    snapshot->position = camera->basePosition;
    func_ov021_020af9a4(camera, &snapshot->direction);
    snapshot->mode = g_cameraManager_020c34e0->mode;
    snapshot->unk_1C = g_cameraManager_020c34e0->unk_E0;
    snapshot->unk_20 = g_cameraManager_020c34e0->unk_E4;
    snapshot->followDistance = g_cameraManager_020c34e0->followDistance;
    snapshot->unk_28 = g_cameraManager_020c34e0->unk_130;
    if (g_cameraManager_020c34e0->mode == 0) {
        snapshot->unk_2C = g_cameraManager_020c34e0->unk_F0;
    }
}
