#include "nitro/types.h"

extern u32 data_ov035_020bc500;

void func_ov035_020ba9ac(u8 value) {
    *(u8 *)(data_ov035_020bc500 + 0x1c) = value;
    *(u16 *)(data_ov035_020bc500 + 6) = *(u16 *)(data_ov035_020bc500 + 6) | 0x4000;
}
