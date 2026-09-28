#include "nitro/types.h"

extern s64 Square64_0203fa2c(s32 value);

u32 SumOfSquaresShift12_0203f9fc(s32 a, s32 b)
{
    s64 sum = Square64_0203fa2c(a) + Square64_0203fa2c(b);
    return (u32)(sum >> 0xc);
}
