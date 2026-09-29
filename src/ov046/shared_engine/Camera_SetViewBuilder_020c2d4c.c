#include "nitro/types.h"

typedef struct CameraView CameraView;
typedef void (*CameraViewBuilder)(CameraView *view);

typedef struct CameraManager {
    u8 pad_00[0x260];
    CameraViewBuilder viewBuilder;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;

void Camera_SetViewBuilder_020c2d4c(CameraViewBuilder builder)
{
    g_cameraManager_020c34e0->viewBuilder = builder;
}
