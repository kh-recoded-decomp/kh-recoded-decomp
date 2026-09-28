#include "nitro/types.h"

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_01ff8684(u32 value, void *dest, u32 size);
extern u32 func_0202a178(u32 size);
extern u32 data_ov001_020a0478;

u32 func_ov001_02068efc(void)
{
    u32 ctx;
    u32 block;

    ctx = (u32)NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a0478 = ctx;
    func_01ff8740(0, (void *)ctx, 0x38);
    *(u8 *)(ctx + 0x11) = 0;
    func_01ff8684(0xffff, (void *)ctx, 0x10);
    block = func_0202a178(0x54);
    *(u32 *)(ctx + 0x34) = block;
    func_01ff8740(0, (void *)block, 0x54);
    *(u16 *)(*(u32 *)(ctx + 0x34) + 0x50) = 0xffff;
    return 0x2068f4d;
}
