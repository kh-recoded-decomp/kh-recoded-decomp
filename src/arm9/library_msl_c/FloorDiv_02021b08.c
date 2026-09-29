#include "nitro/types.h"

typedef struct {
    int quot;
    int rem;
} div_t;

extern int func_02023dbc(int numerator, int denominator);

div_t FloorDiv_02021b08(int numerator, int denominator)
{
    int quotient;
    int remainder;
    int numeratorSign;
    int denominatorSign;
    int resultSign;
    div_t value;

    numeratorSign = 1;
    denominatorSign = 1;

    if (numerator < 0) {
        numerator = -numerator;
        numeratorSign = -1;
    }

    if (denominator < 0) {
        denominatorSign = -1;
        denominator = -denominator;
    }

    resultSign = numeratorSign * denominatorSign;
    quotient = resultSign * func_02023dbc(numerator, denominator);
    remainder = (numerator * numeratorSign) - (quotient * denominator * denominatorSign);

    if (remainder != 0 && resultSign < 0) {
        remainder += denominator * denominatorSign;
        quotient--;
    }

    value.quot = quotient;
    value.rem = remainder;
    return value;
}
