#include "nitro/types.h"

extern s32 data_020534d0[];

BOOL IsValueInTable_02027ebc(s32 value)
{
    s32 index = 0;

    do {
        if (value == data_020534d0[index]) {
            return FALSE;
        }
        index = index + 1;
    } while (index < 0x13);

    return TRUE;
}
