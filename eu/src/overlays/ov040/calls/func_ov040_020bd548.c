#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern void func_ov001_0206a72c();

u32 func_ov040_020bd548(void)
{
    u32 base;

    base = data_ov035_020bc4e0;
    func_ov001_0206a72c((int)*(s8 *)(data_ov035_020bc4e0 + 0x1c));
    *(u16 *)(base + 6) = *(u16 *)(base + 6) | 0x20;
    return 0xb;
}
