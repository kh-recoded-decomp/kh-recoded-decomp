#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    void *messageHandle;
    u8 pad_30[0x3c - 0x30];
    u8 cameraPath[0x60];
} SpecialActionWork;

extern SpecialActionWork *gSpecialActionWork;

extern void func_ov010_020a0d20(SpecialActionWork *work);
extern void ZeroHalfThenFree(void *handle);
extern void CameraPath_Free(void *path);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void ReleaseSpecialActionWork(void)
{
    if (gSpecialActionWork != NULL) {
        func_ov010_020a0d20(gSpecialActionWork);
        ZeroHalfThenFree(gSpecialActionWork->messageHandle);
        CameraPath_Free(gSpecialActionWork->cameraPath);
        NNSi_FndFreeFromDefaultHeap(gSpecialActionWork);
    }
    gSpecialActionWork = NULL;
}
