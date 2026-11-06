#include "nitro/types.h"

extern void FreeSceneListObject(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

extern u32 gMessageWindowWork;

void ReleaseMessageWindowWork(void)
{
    u32 context;

    context = gMessageWindowWork;
    if (*(u32 *)(gMessageWindowWork + 0xd4) != 0) {
        FreeSceneListObject();
        *(u32 *)(context + 0xd4) = 0;
    }
    NNSi_FndFreeFromDefaultHeap((void *)*(u32 *)(context + 0xd0));
    gMessageWindowWork = 0;
}
