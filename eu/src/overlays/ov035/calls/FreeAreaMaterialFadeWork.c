#include "nitro/types.h"

extern u32 data_ov035_020bc504;
extern void ReleaseAreaFadeModelIfLoaded(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeAreaMaterialFadeWork(void) {
    ReleaseAreaFadeModelIfLoaded();
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov035_020bc504 + 0x10c));
    NNSi_FndFreeFromDefaultHeap((void *)data_ov035_020bc504);
}
