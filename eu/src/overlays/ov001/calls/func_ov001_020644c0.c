#include "nitro/types.h"

extern u32 data_ov001_020a0480;

s32 func_ov001_020644c0(void) {
    return (s32)*(s16 *)(data_ov001_020a0480 + 0x20a);
}
