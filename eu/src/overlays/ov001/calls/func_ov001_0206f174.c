#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(u32 handle);
extern void func_ov027_020b7e1c(u32 context);
extern void FreeAllocatedBuffers(u32 context);

void func_ov001_0206f174(u32 context)
{
    func_ov027_020b7e1c(context + 0x1c);
    FreeAllocatedBuffers(context);
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(context + 0x470));
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(context + 0x614));
    *(u32 *)(context + 0x614) = 0;
}
