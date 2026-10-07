#include "nitro/types.h"

typedef struct MarkedSceneWork {
    u8 pad_00[0x68];
    void *resourceBlock;
    void *cameraPath;
} MarkedSceneWork;

extern void ZeroHalfThenFree(void *ptr);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseMarkedSceneResources(MarkedSceneWork *work)
{
    ZeroHalfThenFree(work->resourceBlock);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
