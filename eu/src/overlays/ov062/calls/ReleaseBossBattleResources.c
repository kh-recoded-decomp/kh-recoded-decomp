#include "nitro/types.h"

typedef struct BossBattleWork {
    u8 pad_00[0x88];
    void *resourceBlock;
    u8 pad_8c[4];
    void *cameraPath;
} BossBattleWork;

extern void ZeroHalfThenFree(void *ptr);
extern void func_ov021_020adfd8(BossBattleWork *work, u32 flags);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseBossBattleResources(BossBattleWork *work, u32 flags)
{
    ZeroHalfThenFree(work->resourceBlock);
    func_ov021_020adfd8(work, flags);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
