#include "src/runtime/CalendarFields.h"

extern void FloorDiv(int *out, int value, int divisor);
extern int TryAddInt32A(int *field, int addend);

int NormalizeCalendarFieldWithCarry(int *field, int divisor, int *carry)
{
    int out[2];
    FloorDiv(out, *field, divisor);
    *field = out[1];
    return TryAddInt32A(carry, out[0]);
}
