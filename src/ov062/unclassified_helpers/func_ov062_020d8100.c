#include "nitro/types.h"

extern u32 func_ov001_0206db5c();
extern void func_ov046_020c2f44();
extern u32 func_ov052_020d1170();

s32 func_ov062_020d8100(int self, s32 *event, u32 *errorCode)
{
    s32 handle;

    handle = func_ov001_0206db5c(*(u32 *)(self + 0x14));
    *(u8 *)(handle + 0xa51) = 0;
    func_ov046_020c2f44(event[0x24]);
    func_ov052_020d1170(handle, 0);
    *errorCode = 0x18;
    return event[0xf];
}
