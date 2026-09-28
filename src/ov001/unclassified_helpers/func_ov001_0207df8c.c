#include "nitro/types.h"

extern u32 data_ov001_020a04d0;
extern u32 func_ov001_0207123c(void);
extern u32 func_ov001_020711b0(void);
extern void func_ov027_020b9d54(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
extern u32 func_ov027_020b8184(u32 handle, u32 tag);
extern void func_ov027_020b8268(u32 handle, u32 value);

void func_ov001_0207df8c(void)
{
    u8 *context;
    u32 group;
    u32 handle;
    u32 value;

    context = (u8 *)data_ov001_020a04d0;
    group = func_ov001_0207123c();
    handle = func_ov001_020711b0();
    *(u32 *)(context + 8) = 0;
    func_ov027_020b9d54(group, 0xb, 0xe, 0, 4, 2);
    value = func_ov027_020b8184(handle, 0x134);
    func_ov027_020b8268(handle, value);
    value = func_ov027_020b8184(handle, 0x12e);
    func_ov027_020b8268(handle, value);
}
