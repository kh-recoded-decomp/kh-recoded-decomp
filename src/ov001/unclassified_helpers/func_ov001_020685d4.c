#include "nitro/types.h"

extern u32 data_ov001_020a0470;
extern void func_ov001_02087744(void);
extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_ov001_02068958(void);
extern void func_ov001_0209d184(s32 param);

void func_ov001_020685d4(void)
{
    u8 *ctx;

    ctx = (u8 *)data_ov001_020a0470;
    func_ov001_02087744();
    ctx[0x108] = 0;
    func_01ff8740(0, ctx + 8, 0x100);
    func_ov001_02068958();
    func_ov001_0209d184(0);
}
