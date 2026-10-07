#include "nitro/types.h"

typedef struct AuraBattleWork {
    u8 pad_00[0x88];
    void *resourceBlock;
    u8 pad_8c[0x10];
    void *cameraPath;
} AuraBattleWork;

extern void ZeroHalfThenFree(void *ptr);
extern void func_ov021_020adfd8(AuraBattleWork *work, u32 flags);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseAuraBattleResources(AuraBattleWork *work, u32 flags)
{
    ZeroHalfThenFree(work->resourceBlock);
    func_ov021_020adfd8(work, flags);
    CameraPath_Free(work->cameraPath);
    NNSi_FndFreeFromDefaultHeap(work->cameraPath);
}
