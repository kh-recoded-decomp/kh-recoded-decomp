#include "nitro/types.h"

extern u32 func_02024408(u32 a, u32 b);
extern u32 func_02024818(u32 a, u32 b);

void PowThenAddFloat_02049e30(u32 base, u32 addend, s32 exponent)
{
    u32 result;
    s32 i;

    i = 1;
    result = base;
    if (1 < exponent) {
        do {
            result = func_02024408(result, base);
            i = i + 1;
        } while (i < exponent);
    }
    func_02024818(result, addend);
}
