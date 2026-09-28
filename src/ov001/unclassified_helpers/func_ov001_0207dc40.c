#include "nitro/types.h"

extern u32 data_ov001_020a04d0;
extern void *func_0202a764(void);
extern void func_01ff8830(void *dest, s32 value, u32 size);
extern void func_ov001_0207d728(void *context);
extern void *func_0202a178(u32 size);
extern void func_01ff869c(void *dest, void *src, u32 size);
extern void func_ov001_0207dcb8(void);

u32 func_ov001_0207dc40(u8 *param)
{
    u8 *context;

    context = func_0202a764();
    data_ov001_020a04d0 = (u32)context;
    func_01ff8830(context, 0, 0x4c);
    func_ov001_0207d728(context);
    *(void **)(context + 0x30) = func_0202a178(0x20);
    *(void **)(context + 0x34) = func_0202a178(0x20);
    func_01ff869c(param + 0x1a0, *(void **)(context + 0x30), 0x20);
    func_01ff869c(param + 0x1c0, *(void **)(context + 0x34), 0x20);
    return (u32)func_ov001_0207dcb8;
}
