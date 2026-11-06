#include "nitro/types.h"

extern u32 gFieldSceneEntryContext;
extern void ShutdownSceneContext(void);
extern void ZeroHalfThenFree(void *block);
extern void FreeLayerContextData(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroySceneEntryContext(void)
{
    u8 *ctx;

    ctx = (u8 *)gFieldSceneEntryContext;
    ShutdownSceneContext();
    ZeroHalfThenFree(*(void **)(ctx + 4));
    FreeLayerContextData();
    NNSi_FndFreeFromDefaultHeap((void *)gFieldSceneEntryContext);
    gFieldSceneEntryContext = 0;
}
