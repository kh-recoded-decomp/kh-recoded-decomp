#include "nitro/types.h"

extern u32 func_ov001_020711b0(void);
extern void GFXi_EnqueueCommand_02014090(u32 a, u32 b, u32 c, u32 d);
extern u32 func_ov027_020b8184(u32 handle, u32 tag);
extern void func_ov027_020b8210(u32 handle, u32 value);
extern u32 func_0202a7a4(void);

void func_ov001_0207d800(u8 *context, u32 param)
{
    u32 handle;
    u32 value;

    handle = func_ov001_020711b0();
    GFXi_EnqueueCommand_02014090(7, 0x5400, param, 0x300);
    value = func_ov027_020b8184(handle, 0x134);
    func_ov027_020b8210(handle, value);
    *(u32 *)(context + 0x14) = func_0202a7a4();
}
