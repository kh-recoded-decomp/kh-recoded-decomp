#include "nitro/types.h"

typedef struct SweepSceneWork {
    u8 pad_00[0x84];
    void *resourceBlock;
    void *cameraPath;
} SweepSceneWork;

extern void ZeroHalfThenFree(void *ptr);
extern void FreeResourceSlots(SweepSceneWork *work, u32 flags);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseSweepSceneResources(SweepSceneWork *work, u32 flags)
{
    ZeroHalfThenFree(work->resourceBlock);
    FreeResourceSlots(work, flags);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
