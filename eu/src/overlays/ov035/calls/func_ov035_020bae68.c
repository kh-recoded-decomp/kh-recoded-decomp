#include "nitro/types.h"

extern u32 data_ov035_020bc500;

void func_ov035_020bae68(u8 mode, u16 width, u16 height) {
    u32 base;

    base = data_ov035_020bc500;
    *(u16 *)(data_ov035_020bc500 + 0x46) = width;
    *(u16 *)(base + 0x48) = height;
    *(u8 *)(base + 0x1e) = mode;
}
