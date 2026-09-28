#include "nitro/types.h"

extern s32 func_02027304(s32 flagId);

s32 CountSetFlagsInRange_02066f7c(void) {
    s32 count = 0;
    s32 index = 0;
    s32 result;

    do {
        result = func_02027304(index + 0xf1a);
        index = index + 1;
        if (result != 0) {
            count = count + 1;
        }
    } while (index < 0x1e);
    return count;
}
