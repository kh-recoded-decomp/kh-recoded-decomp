#include "nitro/types.h"

extern u32 gAreaSceneMaterialFadeWork;
extern void ReleaseAreaFadeModelIfLoaded(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeAreaMaterialFadeWork(void) {
    ReleaseAreaFadeModelIfLoaded();
    NNSi_FndFreeFromDefaultHeap(*(void **)(gAreaSceneMaterialFadeWork + 0x10c));
    NNSi_FndFreeFromDefaultHeap((void *)gAreaSceneMaterialFadeWork);
}
