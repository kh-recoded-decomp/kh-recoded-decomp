#include "nitro/types.h"

extern u32 data_ov001_020a0460;

u32 func_ov001_02063b68(s32 index) {
    return *(u32 *)(data_ov001_020a0460 + index * 4 + 0x2938);
}
