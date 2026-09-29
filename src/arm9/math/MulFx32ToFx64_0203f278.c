#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 func_0203f29c(s64 value);

s64 MulFx32ToFx64_0203f278(fx32 a, fx32 b)
{
    return func_0203f29c(((s64)a * b + 0x800) >> 12);
}
