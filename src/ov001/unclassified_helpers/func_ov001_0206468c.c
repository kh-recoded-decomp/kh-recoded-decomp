#include "nitro/types.h"

extern u32 data_ov001_020a0460;

u32 func_ov001_0206468c(s32 index) {
    return *(u32 *)(data_ov001_020a0460 + index * 8 + 0x283c);
}
