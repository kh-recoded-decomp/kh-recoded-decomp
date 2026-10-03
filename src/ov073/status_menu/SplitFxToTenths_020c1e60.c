#include "nitro/types.h"
#include "nitro/fx_types.h"

void SplitFxToTenths_020c1e60(fx32 value, int *whole, int *tenths)
{
    int hundredths = (int)((value & 0xfff) * 100) / 4096;

    *whole = value / 4096;
    *tenths = hundredths / 10;
    if (hundredths % 10 >= 5) {
        if (++*tenths == 10) {
            *tenths = 0;
            (*whole)++;
        }
    }
}
