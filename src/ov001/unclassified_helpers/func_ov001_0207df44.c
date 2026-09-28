#include "nitro/types.h"

extern u32 data_ov001_020a04d0;
extern u32 func_ov001_020711b0(void);
extern u32 func_0202a7a4(void);
extern u32 func_ov027_020b8184(u32 handle, u32 tag);
extern void func_ov027_020b8210(u32 handle, u32 value);
extern void func_ov001_0207d984(void *context);

void func_ov001_0207df44(u32 param, u8 flag)
{
    u8 *context;
    u32 handle;
    u32 value;

    context = (u8 *)data_ov001_020a04d0;
    handle = func_ov001_020711b0();
    context[0] = 0;
    context[1] = flag;
    value = func_0202a7a4();
    *(u32 *)(context + 0x10) = value;
    *(u32 *)(context + 0x18) = 0;
    *(u32 *)(context + 0x1c) = param;
    value = func_ov027_020b8184(handle, 0x12e);
    func_ov027_020b8210(handle, value);
    func_ov001_0207d984(context);
    *(u32 *)(context + 8) = 1;
}
