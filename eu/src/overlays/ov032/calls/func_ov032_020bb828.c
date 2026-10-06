#include "nitro/types.h"

extern u32 data_ov032_020c0080;

s32 func_ov032_020bb828(void) {
    s8 index = *(s8 *)(data_ov032_020c0080 + 0x55);
    return (s32)*(s8 *)(data_ov032_020c0080 + index + 0x56);
}
