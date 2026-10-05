#include "nitro/types.h"

extern int FixedPointMultiply12(int left, int right);
extern int FX_Div_01ff9c84(int numer, int denom);

int RemapIntoDisplayRange_020b699c(int start, int end, int value)
{
    int result = 0x21000;
    result += FX_Div_01ff9c84(FixedPointMultiply12(0xbe000, value - start), end - start);
    return result;
}
