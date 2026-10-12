#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 fov;
} CameraView;

typedef void (*CameraViewBuilder)(CameraView *view);
typedef struct CameraManager {
    u8 pad_00[0x80];
    int type;
    u8 pad_84[0x138 - 0x84];
    void *controller;
    u8 controllerData[4];
} CameraManager;

extern CameraManager *gCameraManager;
extern int gCameraLayerIdsByMode[];
extern int gCameraLayerIds[];
extern void GetSegmentState(CameraManager *manager, CameraView *view);
extern void func_02029fac(int layer, int id);
extern void func_02029f8c(int layer, int id);
extern void *StartEventCamera(void *data, CameraView *current, CameraView *target,
                              int curve, int duration, int returnMode);
extern void Camera_SetViewBuilder(CameraViewBuilder builder);
extern void Camera_FollowAlongViewDirection(CameraView *view);
extern void Camera_AimViewAtPlayer(CameraView *view);
extern void Camera_UpdateController(void);

/* Blend from the current camera view, then restore the requested view builder. */
void Camera_BlendToView(int returnMode, CameraView *target, int curve, int duration,
                       CameraViewBuilder builder)
{
    CameraView current;

    GetSegmentState(gCameraManager, &current);
    if (gCameraManager->type != 2) {
        func_02029fac(0, gCameraLayerIdsByMode[gCameraManager->type]);
        func_02029f8c(0, gCameraLayerIds[2]);
    }
    gCameraManager->controller = StartEventCamera(
        gCameraManager->controllerData, &current, target, curve, duration, returnMode);
    gCameraManager->type = 2;
    if (builder != NULL) {
        Camera_SetViewBuilder(builder);
    } else {
        switch (returnMode) {
        case 0: break;
        case 1: Camera_SetViewBuilder(Camera_FollowAlongViewDirection); break;
        case 2: break;
        case 3: Camera_SetViewBuilder(Camera_AimViewAtPlayer); break;
        }
    }
    if (duration == 0) {
        Camera_UpdateController();
    }
}
