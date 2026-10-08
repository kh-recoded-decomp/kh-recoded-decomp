#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *cameraPath;
    void *messageHandle;
} Ov071SceneState;

extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void ZeroHalfThenFree(void *handle);

void ReleaseOv071CameraResources(Ov071SceneState *state)
{
    CameraPath_Free(state->cameraPath);
    NNSi_FndFreeFromDefaultHeap(state->cameraPath);
    ZeroHalfThenFree(state->messageHandle);
}
