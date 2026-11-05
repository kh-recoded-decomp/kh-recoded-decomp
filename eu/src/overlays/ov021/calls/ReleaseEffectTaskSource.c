#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap();
extern void ReleaseSourceByKind();

void ReleaseEffectTaskSource(int self)
{
    ReleaseSourceByKind(*(u32 *)(self + 0x50));
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(self + 0x50));
}
