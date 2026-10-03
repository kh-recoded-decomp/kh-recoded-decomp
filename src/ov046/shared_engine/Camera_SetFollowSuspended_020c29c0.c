#include "nitro/types.h"

typedef struct FollowControl {
    u8 pad_00[0x94];
    s32 distance;
    s32 blendTimer;
    s32 height;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0xe4];
    s32 followPreset;
    u8 pad_e8[0xf0 - 0xe8];
    u32 stateFlags;
    u8 pad_f4[0x138 - 0xf4];
    void *controller;
    u8 controllerData[4];
} CameraManager;

typedef struct GameSettings {
    u8 pad_00[0x2878];
    u32 unk0 : 2;
    u32 invertCamera : 1;
} GameSettings;

extern CameraManager *g_cameraManager_020c34e0;
extern GameSettings *data_0205fe0c;
extern u32 func_ov046_020c2ab8(CameraManager *camera);
extern s32 func_ov046_020c0d68(void);
extern s32 func_ov046_020c1a70(s32 preset);
extern s32 func_ov046_020c1a48(s32 preset);
extern void Camera_SetStateFlag18_020c2a84(BOOL enable);

void Camera_SetFollowSuspended_020c29c0(BOOL suspended)
{
    CameraManager *camera = g_cameraManager_020c34e0;

    if (!suspended) {
        if (data_0205fe0c->invertCamera == 1) {
            camera->stateFlags |= 0x10000000;
        }
        if (func_ov046_020c2ab8(camera)) {
            if (func_ov046_020c0d68() == 0) {
                ((FollowControl *)g_cameraManager_020c34e0->controllerData)->blendTimer = 0;
            }
            if (camera->stateFlags & 0x80000) {
                camera->stateFlags &= ~0x80000;
                if (func_ov046_020c0d68() == 0) {
                    FollowControl *follow = (FollowControl *)g_cameraManager_020c34e0->controllerData;
                    follow->distance = func_ov046_020c1a70(camera->followPreset);
                    follow->height = func_ov046_020c1a48(camera->followPreset);
                }
            }
        }
    } else {
        camera->stateFlags &= ~0x10000000;
    }
    Camera_SetStateFlag18_020c2a84(suspended);
}




