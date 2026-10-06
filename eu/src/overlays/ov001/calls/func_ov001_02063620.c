#include "nitro/types.h"

extern u32 data_ov001_020a0480;

u32 func_ov001_02063620(void) {
    return (s32)*(s8 *)(data_ov001_020a0480 + 0x2738) & 0x81;
}
