#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov001_02069214(void);
extern void func_0202a1c4(void *block);
extern u32 data_ov001_020a0478;

void func_ov001_02068ff4(void)
{
    u8 *ctx;

    ctx = (u8 *)NNSi_FndGetCurrentRootHeap_0202a764();
    func_ov001_02069214();
    func_0202a1c4((void *)*(u32 *)(ctx + 0x34));
    data_ov001_020a0478 = 0;
}
