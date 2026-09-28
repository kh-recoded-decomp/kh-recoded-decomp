#include "nitro/types.h"

BOOL func_0200a1d8(int id) {
    u32 offset = (u32)(id - 9);
    BOOL result = FALSE;

    if (offset > 0x1a) {
        return result;
    }
    if (1 << offset & 0x400030f) {
        result = TRUE;
    }
    return result;
}
