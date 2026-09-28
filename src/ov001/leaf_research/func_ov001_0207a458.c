#include "nitro/types.h"

extern u32 NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void MI_CpuFill8_01ff8830(void *dst, u8 val, u32 size);
extern u32 func_ov001_02071248(u32 size);
extern u32 func_0202c478(u32 block, u32 align);
extern void func_020524e8(void *obj);

extern u32 g_activeContext_020a04c4;

u32 func_ov001_0207a458(void)
{
    u32 context;
    u32 block;

    context = NNSi_FndGetCurrentRootHeap_0202a764();
    g_activeContext_020a04c4 = context;
    MI_CpuFill8_01ff8830((void *)context, 0, 0xfc);
    *(u32 *)(context + 4) = 0;
    block = func_ov001_02071248(0x2d);
    block = func_0202c478(block, 0xe);
    *(u32 *)(context + 0xd0) = block;
    *(u32 *)(context + 0xf8) = 1;
    func_020524e8((void *)(context + 0xd8));
    return 0x207a4d1;
}
