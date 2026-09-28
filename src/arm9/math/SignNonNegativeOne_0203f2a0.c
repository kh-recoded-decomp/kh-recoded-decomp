#include "nitro/types.h"

s32 SignNonNegativeOne_0203f2a0(s32 value)
{
    s32 sign;
    if (value >= 0) {
        sign = 1;
    } else {
        sign = -1;
    }
    return sign;
}
