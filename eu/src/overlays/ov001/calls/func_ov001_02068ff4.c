#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov001_02069214(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 data_ov001_020a0498;

void func_ov001_02068ff4(void)
{
    u8 *ctx;

    ctx = (u8 *)NNSi_FndGetCurrentRootHeap();
    func_ov001_02069214();
    NNSi_FndFreeFromDefaultHeap((void *)*(u32 *)(ctx + 0x34));
    data_ov001_020a0498 = 0;
}
