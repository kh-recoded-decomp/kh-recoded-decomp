#include "nitro/types.h"

double Fabs_02022ac4(double x, double y) {
    u32 *p = (u32 *)&x;
    p[1] &= 0x7fffffff;
    return x;
}
