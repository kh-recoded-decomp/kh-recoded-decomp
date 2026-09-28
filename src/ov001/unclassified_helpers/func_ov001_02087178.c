#include "nitro/types.h"

extern u32 data_ov001_020a04dc;

void func_ov001_02087178(void) {
    if ((*(u8 *)(data_ov001_020a04dc + 5) & 2) != 0) {
        *(u8 *)(data_ov001_020a04dc + 5) |= 0xc;
    }
}
