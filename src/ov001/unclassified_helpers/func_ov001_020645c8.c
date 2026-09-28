#include "nitro/types.h"

extern u32 func_ov001_02064574();

BOOL func_ov001_020645c8(u32 value) {
    s32 result = func_ov001_02064574(value, 1);
    return result != 0;
}
