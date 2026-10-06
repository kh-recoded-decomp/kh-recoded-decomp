#include "nitro/types.h"

extern u32 data_ov001_020a04f0;
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void func_ov001_0207dcbc(void)
{
    u8 *context;

    context = (u8 *)data_ov001_020a04f0;
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov001_020a04f0 + 0x30));
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x34));
    NNSi_FndFreeFromDefaultHeap(*(void **)(context + 0x38));
    data_ov001_020a04f0 = 0;
}
