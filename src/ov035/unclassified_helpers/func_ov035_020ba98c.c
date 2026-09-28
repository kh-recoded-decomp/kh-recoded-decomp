#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;

void func_ov035_020ba98c(u8 value) {
    *(u8 *)(data_ov035_020bc4e0 + 0x1c) = value;
    *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x4000;
}
