#include "nitro/fx_types.h"

fx32 FX_Mul32x64c_02006468(fx32 value, fx64c scale)
{
    fx64c product = scale * value + 0x80000000LL;
    return (fx32)(product >> 32);
}
