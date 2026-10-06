#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap();
extern void ReleaseSourceByKind();

void func_ov021_020ad064(int self)
{
    ReleaseSourceByKind(*(u32 *)(self + 0x50));
    NNSi_FndFreeFromDefaultHeap(*(u32 *)(self + 0x50));
}
