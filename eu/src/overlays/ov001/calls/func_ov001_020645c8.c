#include "nitro/types.h"

extern u32 ReadSessionPackedBits();

BOOL func_ov001_020645c8(u32 value) {
    s32 result = ReadSessionPackedBits(value, 1);
    return result != 0;
}
