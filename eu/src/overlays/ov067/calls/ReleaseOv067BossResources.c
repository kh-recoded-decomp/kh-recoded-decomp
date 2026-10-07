#include "nitro/types.h"

typedef struct Ov067BossWork {
    u8 pad_00[0x84];
    u8 cameraPath[0x6c];
    void *resourceBlock;
} Ov067BossWork;

extern void CameraPath_Free(void *path);
extern void FreeResourceSlots(Ov067BossWork *work, u32 flags);
extern void ZeroHalfThenFree(void *ptr);

void ReleaseOv067BossResources(Ov067BossWork *work, u32 flags)
{
    CameraPath_Free(work->cameraPath);
    FreeResourceSlots(work, flags);
    ZeroHalfThenFree(work->resourceBlock);
}
