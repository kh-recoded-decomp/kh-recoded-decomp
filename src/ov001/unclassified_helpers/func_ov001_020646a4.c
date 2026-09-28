#include "nitro/types.h"

extern u32 data_ov001_020a0460;

u32 func_ov001_020646a4(s32 index) {
    return *(u32 *)(data_ov001_020a0460 + index * 8 + 0x2840);
}
