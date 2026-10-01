#include "nitro/types.h"

extern s64 func_02023ba4(s64 numerator, s64 denominator);

s64 DivFx64Shifted_020496b4(s64 numerator, s64 denominator)
{
    return func_02023ba4(numerator << 16, denominator << 16);
}
