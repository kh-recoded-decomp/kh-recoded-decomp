#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern void func_ov001_02066810();
extern void func_ov001_02087628();

u32 func_ov040_020bd5e4(void)
{
    func_ov001_02066810();
    func_ov001_02087628(1);
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x20;
    return 0xf;
}
