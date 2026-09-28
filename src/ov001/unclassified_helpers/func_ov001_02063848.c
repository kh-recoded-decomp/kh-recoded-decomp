#include "nitro/types.h"

extern u32 data_ov001_020a0460;

void func_ov001_02063848(u8 param1, u8 param2) {
    u32 base = data_ov001_020a0460;
    *(u8 *)(data_ov001_020a0460 + 0x2744) = param1;
    *(u8 *)(base + 0x2745) = param2;
}
