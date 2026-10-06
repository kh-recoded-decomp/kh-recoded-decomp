#include "nitro/types.h"

extern u32 DecrementByteCounter();
extern u32 func_ov001_02064a30();

void func_ov001_02064aa8(u16 *value) {
    s32 result = func_ov001_02064a30(*value);
    if (result != 0) {
        DecrementByteCounter(*value);
    }
}
