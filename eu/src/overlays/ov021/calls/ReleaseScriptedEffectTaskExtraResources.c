#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap();
extern void ReleaseCallbackOwnedBuffer();
extern void FreeResourceSlots();

void ReleaseScriptedEffectTaskExtraResources(int self)
{
    FreeResourceSlots();
    ReleaseCallbackOwnedBuffer(*(u32 *)(self + 0x84));
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(self + 0x84));
}
