#include "nitro/types.h"

extern void DestroyFndObjectList(u32 context);
extern void NNSi_FndFreeFromDefaultHeap(u32 handle);
extern void ReleaseResourceWithBuffers(u32 context, u32 count);

void func_ov001_0206f648(u32 context)
{
    s32 index;

    DestroyFndObjectList(context + 0x18c);
    DestroyFndObjectList(context + 0x1c0);
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(context + 500));
    index = 0;
    do {
        NNSi_FndFreeFromDefaultHeap(*(u32 *)(context + index * 4 + 0xb34));
        index = index + 1;
    } while (index < 0x200);
    ReleaseResourceWithBuffers(context + 0x1338, 0xe);
}
