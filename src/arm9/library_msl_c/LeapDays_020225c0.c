#include "nitro/types.h"

typedef struct {
    int quot;
    int rem;
} div_t;

extern div_t div_02021998(int numerator, int denominator);
extern div_t FloorDiv_02021b08(int numerator, int denominator);
extern int func_02022570(int year);

int LeapDays_020225c0(int year, int month)
{
    int days;
    div_t q;

    q = div_02021998(year, 4);
    days = q.quot;

    q = div_02021998(year, 100);
    days -= q.quot;

    if (year < 100) {
        q = FloorDiv_02021b08(year + 899, 1000);
        days += q.quot;
    } else {
        q = FloorDiv_02021b08(year - 100, 1000);
        days += q.quot + 1;
    }

    if (func_02022570(year)) {
        if (year < 0) {
            if (month > 1) {
                ++days;
            }
        } else if (month <= 1) {
            --days;
        }
    }

    return days;
}
