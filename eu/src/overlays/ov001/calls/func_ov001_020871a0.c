#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

void func_ov001_020871a0(void) {
    if ((*(u8 *)(data_ov001_020a04fc + 5) & 2) != 0) {
        *(u8 *)(data_ov001_020a04fc + 5) |= 0xc;
    }
}
