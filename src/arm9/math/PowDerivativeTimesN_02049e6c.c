#include "nitro/types.h"

extern u32 func_02024408(u32 a, u32 b);
extern u32 func_02023a98(s32 value);

void PowDerivativeTimesN_02049e6c(u32 base, s32 n)
{
    s32 i;
    u32 result;
    u32 nFixed;

    result = base;
    i = 1;
    if (1 < n - 1) {
        do {
            result = func_02024408(result, base);
            i = i + 1;
        } while (i < n - 1);
    }
    nFixed = func_02023a98(n);
    func_02024408(nFixed, result);
}
