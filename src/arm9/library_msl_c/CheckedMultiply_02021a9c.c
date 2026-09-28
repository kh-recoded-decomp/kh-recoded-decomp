#include "nitro/types.h"

extern int func_02023dbc(int numerator, int denominator);

BOOL CheckedMultiply_02021a9c(int *value, int factor)
{
    int multiplicand = *value;
    int multiplier = factor;
    int sign = ((multiplicand < 0) ^ (multiplier < 0)) ? -1 : 1;

    if (multiplicand < 0) {
        multiplicand = -multiplicand;
    }

    if (multiplier < 0) {
        multiplier = -multiplier;
    }

    if (multiplicand > func_02023dbc(0x7FFFFFFF, multiplier)) {
        return FALSE;
    }

    *value = multiplicand * multiplier * sign;
    return TRUE;
}
