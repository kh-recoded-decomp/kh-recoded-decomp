#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x84];
    u8 cameraPath[0x70];
    void *messageHandle;
} Ov069BossObject;

extern void CameraPath_Free(void *path);
extern void FreeResourceSlots(Ov069BossObject *object, void *resources);
extern void ZeroHalfThenFree(void *handle);

void ReleaseOv069BossResources(Ov069BossObject *object, void *resources)
{
    CameraPath_Free(object->cameraPath);
    FreeResourceSlots(object, resources);
    ZeroHalfThenFree(object->messageHandle);
}
