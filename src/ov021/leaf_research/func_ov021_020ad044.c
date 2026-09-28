#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4();
extern void func_ov056_020d7d20();

void func_ov021_020ad044(int self)
{
    func_ov056_020d7d20(*(u32 *)(self + 0x50));
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(u32 *)(self + 0x50));
}
