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

extern SceneContext data_ov036_020c3920;
extern void SetSoundListenersEnabled_0204df9c(int enabled);
extern void PXI_Init_0202a638(void *handle);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern int ZeroHalfThenFree_0202cd78(void *resource);
extern void func_020257e4(void *channel);
extern void StoreGlobalArrayEntry_02025668(int index, int value);

void ShutdownSceneWork_020ba6a4(void)
{
    SceneWork *work = data_ov036_020c3920.work;

    SetSoundListenersEnabled_0204df9c(0);
    PXI_Init_0202a638(work->pxiHandle);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(work->slotBuffer);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(work->layers);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(work->viewers);
    ZeroHalfThenFree_0202cd78(work->resourceB);
    ZeroHalfThenFree_0202cd78(work->resourceA);
    ZeroHalfThenFree_0202cd78(work->resourceC);
    if (work->resourceD != NULL) {
        ZeroHalfThenFree_0202cd78(work->resourceD);
    }
    func_020257e4(work->channelA);
    func_020257e4(work->channelB);
    StoreGlobalArrayEntry_02025668(5, 0);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov036_020c3920.buffer);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov036_020c3920.extra);
    REG_BG1CNT &= ~0x40;
    data_ov036_020c3920.work = NULL;
}
