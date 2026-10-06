#include "nitro/types.h"

extern u32 data_ov001_020a04fc;

void func_ov001_0208707c(int enable) {
    if (enable != 0) {
        *(u8 *)(data_ov001_020a04fc + 5) |= 0xc0;
        return;
    }
    *(u8 *)(data_ov001_020a04fc + 5) &= 0xbf;
}
