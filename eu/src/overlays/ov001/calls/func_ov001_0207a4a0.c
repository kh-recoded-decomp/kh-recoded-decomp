#include "nitro/types.h"

extern void FreeSceneListObject(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

extern u32 data_ov001_020a04e4;

void func_ov001_0207a4a0(void)
{
    u32 context;

    context = data_ov001_020a04e4;
    if (*(u32 *)(data_ov001_020a04e4 + 0xd4) != 0) {
        FreeSceneListObject();
        *(u32 *)(context + 0xd4) = 0;
    }
    NNSi_FndFreeFromDefaultHeap((void *)*(u32 *)(context + 0xd0));
    data_ov001_020a04e4 = 0;
}
