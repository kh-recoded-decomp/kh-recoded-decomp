#include "nitro/types.h"

extern u32 func_ov001_02068e80(void);
extern u32 UnsignedDivide_02023fc8(u32 numerator, u32 denominator);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

void SaveElapsedSeconds_020630bc(void)
{
    int seconds = UnsignedDivide_02023fc8(func_ov001_02068e80(), 1000);

    if (seconds >= 0x20000) {
        seconds = 0x1ffff;
    }
    WriteSessionPackedBits_0206459c(0x35d2, 0x11, seconds);
}
