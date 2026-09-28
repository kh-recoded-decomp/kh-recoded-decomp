#include "nitro/types.h"

extern u32 data_ov001_020a0464;

u32 func_ov001_0206685c(void) {
    if (*(s32 *)(data_ov001_020a0464 + 0x4c) != 0) {
        return 1;
    }
    return 0;
}
