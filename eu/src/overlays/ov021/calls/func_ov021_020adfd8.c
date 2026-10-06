#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap();
extern void ReleaseCallbackOwnedBuffer();
extern void FreeResourceSlots();

void func_ov021_020adfd8(int self)
{
    FreeResourceSlots();
    ReleaseCallbackOwnedBuffer(*(u32 *)(self + 0x84));
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(self + 0x84));
}
