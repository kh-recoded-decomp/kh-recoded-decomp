#include "nitro/types.h"

extern u32 NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitMessageLoaders(void);

extern u32 data_ov001_020a04b8;

void func_ov001_0206c9c0(void)
{
    if (data_ov001_020a04b8 == 0) {
        data_ov001_020a04b8 = NNSi_FndAllocFromDefaultHeap(0xa4);
        InitMessageLoaders();
    }
}
