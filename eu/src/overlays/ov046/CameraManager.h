#ifndef OV046_CAMERA_MANAGER_H
#define OV046_CAMERA_MANAGER_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraManager CameraManager;
typedef void *(*CameraController)(void *data, CameraManager *camera);
typedef int (*CameraUpdate)(void);

struct CameraManager {
    s32 field00;
    s32 field04;
    s32 field08;
    fx32 nearPlane;
    fx32 farPlane;
    u8 reserved14[0x80 - 0x14];
    s32 mode;
    u32 reserved84;
    s32 field88;
    u8 reserved8c[0xdc - 0x8c];
    u32 frameCount;
    u32 stateFlags;
    s32 fieldE4;
    s32 fieldE8;
    u32 prevState;
    u32 state;
    void *focusTarget;
    u8 buffers[0x110 - 0xf8];
    void *buffer110;
    u8 reserved114[0x128 - 0x114];
    u32 bufferFlags;
    fx32 field12c;
    fx32 field130;
    fx32 viewDistance;
    CameraController controller;
    /* Shared storage for the four controller-specific work layouts. */
    u8 controllerData[0x2d8];
};

typedef char CameraManagerSizeCheck[(sizeof(CameraManager) == 0x414) ? 1 : -1];

extern CameraManager *gCameraManager;

#endif
