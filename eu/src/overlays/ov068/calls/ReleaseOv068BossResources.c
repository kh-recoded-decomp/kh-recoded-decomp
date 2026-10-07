#include "nitro/types.h"

typedef struct Ov068BossWork {
    u8 pad_00[0x84];
    u8 cameraPath[0x6c];
    void *resourceBlock;
} Ov068BossWork;

extern void CameraPath_Free(void *path);
extern void FreeResourceSlots(Ov068BossWork *work, u32 flags);
extern void ZeroHalfThenFree(void *ptr);

void ReleaseOv068BossResources(Ov068BossWork *work, u32 flags)
{
    CameraPath_Free(work->cameraPath);
    FreeResourceSlots(work, flags);
    ZeroHalfThenFree(work->resourceBlock);
}
