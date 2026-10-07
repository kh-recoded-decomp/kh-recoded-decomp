#include "nitro/types.h"

extern u32 ReadSessionPackedBits();

BOOL IsSessionFlagSet(u32 value) {
    s32 result = ReadSessionPackedBits(value, 1);
    return result != 0;
}
