#include "nitro/types.h"
#include "nitro/fx_types.h"

#include "src/overlays/ov046/CameraManager.h"

typedef struct CameraDefaultsA {
    u8 reserved00[0x2a];
    s16 field2a;
} CameraDefaultsA;
typedef struct CameraDefaultsB {
    u8 reserved00[0x16];
    s16 field16;
} CameraDefaultsB;

extern const CameraDefaultsA data_02053800;
extern const CameraDefaultsB data_02053ac0;
extern int gCameraLayerIds[];
extern int MaxOfArgs(int count, ...);
extern void func_01ff88c4(void *dest, u32 value, u32 size);
extern void LoadDefaultProjectionValues(void *projection);
extern void Obj_AllocDataBuffers(void *buffers, int size, int first, int second, int third);
extern void Camera_LoadOptionFlags(void);
extern void func_02029f8c(int layer, int id);
extern CameraController Camera_ResetTracking(void *data, CameraManager *camera);
extern int Camera_UpdateController(void);

CameraUpdate Camera_InitManager(void *context, CameraManager *camera)
{
    gCameraManager = camera;
    func_01ff88c4(camera->controllerData, 0,
                 MaxOfArgs(4, sizeof(camera->controllerData), 0x28, 0x1a8, 0x54));
    LoadDefaultProjectionValues(camera);
    camera->farPlane = 0x6a4000;
    camera->field00 = data_02053800.field2a;
    camera->field04 = data_02053ac0.field16;
    camera->nearPlane = 0x19a;
    camera->mode = 0;
    camera->field88 = 0;
    camera->frameCount = 0;
    camera->stateFlags = 0;
    camera->fieldE4 = 0;
    camera->fieldE8 = 0;
    camera->state = 3;
    camera->prevState = 3;
    camera->focusTarget = NULL;
    camera->bufferFlags &= ~1;
    if (camera->buffer110 == NULL) {
        Obj_AllocDataBuffers(camera->buffers, 0x40, 1, 1, 1);
    }
    camera->field12c = FX32_ONE;
    camera->field130 = 0x14cd;
    camera->viewDistance = 0x6000;
    Camera_LoadOptionFlags();
    func_02029f8c(0, gCameraLayerIds[0]);
    gCameraManager->controller = Camera_ResetTracking(gCameraManager->controllerData, camera);
    return Camera_UpdateController;
}
