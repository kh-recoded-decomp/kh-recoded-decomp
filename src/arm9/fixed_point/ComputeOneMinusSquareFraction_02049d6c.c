#include "nitro/types.h"

extern void func_01ff9cfc(u32 value);

void ComputeOneMinusSquareFraction_02049d6c(int value)
{
    s64 squared = (s64)value * (s64)value + 0x800;
    func_01ff9cfc(0x1000 - (u32)(squared >> 0xc));
}
