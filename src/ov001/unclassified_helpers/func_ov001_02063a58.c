#include "nitro/types.h"

extern u32 data_ov001_020a0460;

void func_ov001_02063a58(u8 value) {
    *(u8 *)(data_ov001_020a0460 + 0x27b4) = value;
}
