#include "nitro/types.h"

extern s64 LongDiv_02023ba4(s64 numerator, s64 denominator);

s64 DivideShifted27_0203f4d8(s32 numerator, s32 denominator)
{
    return LongDiv_02023ba4((s64)numerator << 27, denominator);
}
