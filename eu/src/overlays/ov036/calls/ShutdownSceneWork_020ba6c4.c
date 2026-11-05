#include "src/overlays/ov036/Event2DPanel.h"

#define REG_BG1CNT (*(vu16 *)0x0400000a)

extern void SetSoundListenersEnabled(int enabled);
extern void DestroyTaskObjectWrapper(void *handle);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern int ZeroHalfThenFree(void *resource);
extern void ReleaseScriptVmBuffer(void *channel);
extern void StoreGlobalArrayEntry(int index, int value);

void ShutdownSceneWork_020ba6c4(void)
{
    Event2DPanelWork *work = data_ov036_020c3940.work;

    SetSoundListenersEnabled(0);
    DestroyTaskObjectWrapper(work->pxiHandle);
    NNSi_FndFreeFromDefaultHeap(work->slots);
    NNSi_FndFreeFromDefaultHeap(work->layers);
    NNSi_FndFreeFromDefaultHeap(work->actors);
    ZeroHalfThenFree(work->backgroundArchive);
    ZeroHalfThenFree(work->characterArchive);
    ZeroHalfThenFree(work->objectArchive);
    if (work->resourceD != NULL) {
        ZeroHalfThenFree(work->resourceD);
    }
    ReleaseScriptVmBuffer(work->channels[0]);
    ReleaseScriptVmBuffer(work->channels[1]);
    StoreGlobalArrayEntry(5, 0);
    NNSi_FndFreeFromDefaultHeap(data_ov036_020c3940.buffer);
    NNSi_FndFreeFromDefaultHeap(data_ov036_020c3940.extra);
    REG_BG1CNT &= ~0x40;
    data_ov036_020c3940.work = NULL;
}
