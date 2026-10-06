#include "nitro/types.h"

extern void func_ov001_0206c994(int obj);
extern void NNSi_FndFreeFromDefaultHeap(u32 obj);

extern u32 data_ov001_020a04b8;

void func_ov001_0206c9dc(void)
{
    if (data_ov001_020a04b8 != 0) {
        func_ov001_0206c994(data_ov001_020a04b8);
        NNSi_FndFreeFromDefaultHeap(data_ov001_020a04b8);
        data_ov001_020a04b8 = 0;
    }
}
