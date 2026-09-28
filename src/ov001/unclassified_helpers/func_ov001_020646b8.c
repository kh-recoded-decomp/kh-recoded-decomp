#include "nitro/types.h"

extern u32 data_ov001_020a0460;
extern u32 func_0202a1c4();

void func_ov001_020646b8(s32 index) {
    u32 *slot = (u32 *)(data_ov001_020a0460 + 0x283c + index * 8);
    if (*(s32 *)(data_ov001_020a0460 + 0x283c + index * 8) != 0) {
        func_0202a1c4();
        slot[0] = 0;
        slot[1] = 0;
    }
}
