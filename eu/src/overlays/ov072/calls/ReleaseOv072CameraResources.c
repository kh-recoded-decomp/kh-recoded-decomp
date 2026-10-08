#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4c];
    void *cameraPath;
    u8 pad_50[0x7c - 0x50];
    void *messageHandle;
} Ov072SceneState;

extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void ZeroHalfThenFree(void *handle);

void ReleaseOv072CameraResources(Ov072SceneState *state)
{
    CameraPath_Free(state->cameraPath);
    NNSi_FndFreeFromDefaultHeap(state->cameraPath);
    ZeroHalfThenFree(state->messageHandle);
}
