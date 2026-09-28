#include "nitro/types.h"

extern u32 data_ov001_020a04cc;
extern u32 data_ov001_0209efe4;
extern u32 data_ov001_0209efec;
extern void func_01ff8830(void *dest, s32 value, u32 size);
extern void *func_0202a764(void);
extern void func_ov001_0207b7bc();
extern void func_ov001_0207b860(void);

u32 func_ov001_0207b7f0(void)
{
    u8 *context;

    context = func_0202a764();
    func_01ff8830(context, 0, 0x910);
    data_ov001_020a04cc = (u32)context;
    func_ov001_0207b7bc(context + 8, &data_ov001_0209efe4);
    func_ov001_0207b7bc(context + 0xc, &data_ov001_0209efec);
    *(u32 *)(context + 0xe8) = 0x23000;
    *(u32 *)(context + 0xec) = 0x7000;
    return (u32)func_ov001_0207b860;
}
