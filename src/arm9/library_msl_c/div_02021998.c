#include "nitro/types.h"

typedef struct {
    int quot;
    int rem;
} div_t;

extern int func_02023dbc(int numerator, int denominator);

div_t div_02021998(int numerator, int denominator)
{
    int numeratorSign;
    int denominatorSign;
    div_t value;

    numeratorSign = 1;
    denominatorSign = 1;

    if (numerator < 0) {
        numerator = -numerator;
        numeratorSign = -1;
    }

    if (denominator < 0) {
        denominator = -denominator;
        denominatorSign = -1;
    }

    value.quot = func_02023dbc(numerator, denominator);
    value.quot *= numeratorSign * denominatorSign;
    value.rem = (numerator * numeratorSign) - (value.quot * denominator * denominatorSign);

    return value;
}
