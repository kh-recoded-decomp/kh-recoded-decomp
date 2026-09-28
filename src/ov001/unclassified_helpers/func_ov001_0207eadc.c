#include "nitro/types.h"

extern u32 data_ov001_020a04d4;
extern u32 func_ov001_020711b0(void);
extern void func_ov001_0207df8c(void);
extern u32 func_ov027_020b8184(u32 handle, u32 tag);
extern void func_ov027_020b8268(u32 handle, u32 value);

void func_ov001_0207eadc(void)
{
    u32 handle;
    u32 value;

    handle = func_ov001_020711b0();
    func_ov001_0207df8c();
    value = func_ov027_020b8184(handle, 0x12e);
    func_ov027_020b8268(handle, value);
    *(u32 *)(data_ov001_020a04d4 + 0x20) = 0;
}
