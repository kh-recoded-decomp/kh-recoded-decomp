#include "nitro/types.h"

extern u32 data_ov001_020a0480;

void func_ov001_02063560(s32 index, u32 value) {
    *(u32 *)(data_ov001_020a0480 + index * 4 + 0x25b0) = value;
}
