#include "nitro/types.h"

extern u32 data_ov001_020a048c;
extern void ShutdownSceneContext(void);
extern void ZeroHalfThenFree(void *block);
extern void FreeLayerContextData(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov001_0206747c(void)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a048c;
    ShutdownSceneContext();
    ZeroHalfThenFree(*(void **)(ctx + 4));
    FreeLayerContextData();
    NNSi_FndFreeFromDefaultHeap((void *)data_ov001_020a048c);
    data_ov001_020a048c = 0;
}
