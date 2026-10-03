#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef void *(*CameraControllerFunc)(void *data, void *camera);

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    VecFx32 target;
    u8 pad_50[0x80 - 0x50];
    int type;
    u8 pad_84[0xdc - 0x84];
    u32 frameCount;
    u8 pad_e0[0xec - 0xe0];
    u32 prevState;
    u32 state;
    u8 pad_f4[0x138 - 0xf4];
    CameraControllerFunc controller;
    u8 controllerData[4];
} CameraManager;

typedef struct GameEntry {
    u8 pad_00[0x9ac];
    u64 flags;
} GameEntry;

extern CameraManager *g_cameraManager_020c34e0;
extern u16 data_020604fc;
extern GameEntry *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void Camera_BlendToVelocityAim_020c132c(const VecFx32 *velocity, s32 curveType, fx32 duration);

int Camera_UpdateController_020c0a70(void)
{
    VecFx32 direction;
    VecFx32 normalized;
    VecFx32 diff;
    VecFx32 dirCopy;
    CameraControllerFunc next;

    g_cameraManager_020c34e0->prevState = g_cameraManager_020c34e0->state;
    if (g_cameraManager_020c34e0->type != 0 && (GetBoundedEntryField_0206db5c(0)->flags & 0x100000000ULL)) {
        VEC_Subtract_01ff9e3c(&g_cameraManager_020c34e0->target, &g_cameraManager_020c34e0->eye, &diff);
        dirCopy = diff;
        func_01ff9f88(&dirCopy, &normalized);
        direction = normalized;
        Camera_BlendToVelocityAim_020c132c(&direction, 0, FX32_ONE);
        g_cameraManager_020c34e0->controller(g_cameraManager_020c34e0->controllerData, g_cameraManager_020c34e0);
    }
    next = g_cameraManager_020c34e0->controller(g_cameraManager_020c34e0->controllerData, g_cameraManager_020c34e0);
    if (next != NULL) {
        g_cameraManager_020c34e0->controller = next;
    }
    g_cameraManager_020c34e0->frameCount = data_020604fc;
    return 0;
}





