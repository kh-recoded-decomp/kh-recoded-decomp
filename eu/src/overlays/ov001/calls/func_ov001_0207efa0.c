#include "nitro/types.h"

extern u32 data_ov001_020a04f8;
extern void DestroyListNodes(void);
extern void ReleaseResourceAndDetach();
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void ReleaseEffectResources(void);

void func_ov001_0207efa0(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04f8;
    DestroyListNodes();
    *(u32 *)(context + 0x120) = 0;
    if (*(s32 *)(context + 0x11c) != 0) {
        ReleaseResourceAndDetach();
        NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x11c));
        *(u32 *)(context + 0x11c) = 0;
    }
    ReleaseEffectResources();
}
