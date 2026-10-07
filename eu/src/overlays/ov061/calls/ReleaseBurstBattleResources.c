#include "nitro/types.h"

typedef struct BurstBattleWork {
    u8 pad_00[0x84];
    void *resourceBlock;
    u8 pad_88[4];
    void *cameraPath;
} BurstBattleWork;

extern void ZeroHalfThenFree(void *ptr);
extern void FreeResourceSlots(BurstBattleWork *work, u32 flags);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseBurstBattleResources(BurstBattleWork *work, u32 flags)
{
    ZeroHalfThenFree(work->resourceBlock);
    FreeResourceSlots(work, flags);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
