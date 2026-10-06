#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u32 NNSi_FndFreeFromDefaultHeap();

void func_ov001_020646b8(s32 index) {
    u32 *slot = (u32 *)(data_ov001_020a0480 + 0x283c + index * 8);
    if (*(s32 *)(data_ov001_020a0480 + 0x283c + index * 8) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        slot[0] = 0;
        slot[1] = 0;
    }
}
