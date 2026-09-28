#include "nitro/types.h"

extern s32 func_02023dbc(s32 dividend, s32 divisor);

s32 DigitCount_0207b7a4(s32 value)
{
    s32 count;

    count = 0;
    do {
        count = count + 1;
        value = func_02023dbc(value, 10);
    } while (0 < value);
    return count;
}
