#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern u32 data_ov040_020be280;
extern void PlaySoundChecked();
extern int func_ov001_020645c8();
extern void func_ov001_02064184();

u32 func_ov040_020bd418(void)
{
    int ok;

    *(u8 *)(data_ov035_020bc4e0 + 0x84) = 0xf;
    PlaySoundChecked(0x1a0, 0);
    ok = func_ov001_020645c8(0x3308);
    if (ok == 0) {
        func_ov001_02064184(1, 0xffffffff);
    }
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x20;
    *(u16 *)(data_ov035_020bc4e0 + 0x22) = *(u16 *)(data_ov035_020bc4e0 + 0x22) | 0x100;
    *(u16 *)(data_ov035_020bc4e0 + 0x24) = *(u16 *)(data_ov035_020bc4e0 + 0x24) | 0x100;
    *(u16 *)(data_ov040_020be280 + 0x13c) = *(u16 *)(data_ov040_020be280 + 0x13c) | 0x8000;
    return 9;
}
