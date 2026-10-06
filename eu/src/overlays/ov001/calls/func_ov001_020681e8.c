#include "nitro/types.h"

BOOL func_ov001_020681e8(u8 *entry, u32 kind)
{
    u32 value;
    s32 i;

    if (entry != 0) {
        i = 0;
        do {
            value = entry[i + 0xc];
            if (kind == value) {
                return 1;
            }
            if (value == 0) {
                return 0;
            }
            if (value == 8) {
                return 0;
            }
            i = i + 1;
        } while (i < 4);
    }
    return 0;
}
