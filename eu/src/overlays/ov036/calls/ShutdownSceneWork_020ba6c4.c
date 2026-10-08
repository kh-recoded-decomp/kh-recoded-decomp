#include "nitro/types.h"

typedef struct SceneWork {
    u8 pad_0000[0xc];
    void *pxiHandle;
    u8 channelA[0x648];
    u8 channelB[0x9f0];
    void *resourceD;
    void *resourceA;
    void *resourceB;
    void *resourceC;
    u8 pad_1058[0x38];
    void *slotBuffer;
    void *viewers;
    void *layers;
} SceneWork;

typedef struct SceneContext {
    void *buffer;
    SceneWork *work;
    void *extra;
} SceneContext;

#define REG_BG1CNT (*(vu16 *)0x0400000a)

extern SceneContext data_ov036_020c3940;
extern void SetSoundListenersEnabled(int enabled);
extern void PXI_Init_0202a64c(void *handle);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern int ZeroHalfThenFree(void *resource);
extern void func_020257f8(void *channel);
extern void StoreGlobalArrayEntry(int index, int value);

void ShutdownSceneWork_020ba6c4(void)
{
    SceneWork *work = data_ov036_020c3940.work;

    SetSoundListenersEnabled(0);
    PXI_Init_0202a64c(work->pxiHandle);
    NNSi_FndFreeFromDefaultHeap(work->slotBuffer);
    NNSi_FndFreeFromDefaultHeap(work->layers);
    NNSi_FndFreeFromDefaultHeap(work->viewers);
    ZeroHalfThenFree(work->resourceB);
    ZeroHalfThenFree(work->resourceA);
    ZeroHalfThenFree(work->resourceC);
    if (work->resourceD != NULL) {
        ZeroHalfThenFree(work->resourceD);
    }
    func_020257f8(work->channelA);
    func_020257f8(work->channelB);
    StoreGlobalArrayEntry(5, 0);
    NNSi_FndFreeFromDefaultHeap(data_ov036_020c3940.buffer);
    NNSi_FndFreeFromDefaultHeap(data_ov036_020c3940.extra);
    REG_BG1CNT &= ~0x40;
    data_ov036_020c3940.work = NULL;
}
