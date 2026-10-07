#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_propagation off

int ScaleRoundedMillis_020c60e8(fx32 value, int scale)
{
    int fraction = value & 0xfff;
    int millis = fraction * 1000 / 4096;

    if (millis % 10 >= 5) {
        millis += 10 - millis % 10;
    }
    return (millis + (value / 4096) * 1000) * scale / 1000;
}