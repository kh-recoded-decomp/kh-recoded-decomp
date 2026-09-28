#include "nitro/types.h"

extern u32 data_ov001_020a0460;

u32 func_ov001_02065f04(void) {
    *(u8 *)(data_ov001_020a0460 + 0x27b6) = *(u8 *)(data_ov001_020a0460 + 0x27b6) | 0x20;
    return 1;
}
