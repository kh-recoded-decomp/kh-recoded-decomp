#include "nitro/types.h"

extern u32 data_ov001_020a04dc;

void func_ov001_02087054(int enable) {
    if (enable != 0) {
        *(u8 *)(data_ov001_020a04dc + 5) |= 0xc0;
        return;
    }
    *(u8 *)(data_ov001_020a04dc + 5) &= 0xbf;
}
