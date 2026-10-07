#include "nitro/types.h"

typedef struct UnitEffectWork {
    u8 pad_00[0x54];
    void *resourceBlock;
    void *ownedBuffer;
    void *cameraPath;
} UnitEffectWork;

extern void ZeroHalfThenFree(void *ptr);
extern void ReleaseCallbackOwnedBuffer(void *ptr);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseUnitEffectResources(UnitEffectWork *work)
{
    ZeroHalfThenFree(work->resourceBlock);
    ReleaseCallbackOwnedBuffer(work->ownedBuffer);
    NNSi_FndFreeFromDefaultHeap(work->ownedBuffer);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
