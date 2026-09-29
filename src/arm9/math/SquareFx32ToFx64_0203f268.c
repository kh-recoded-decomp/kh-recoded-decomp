#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 MulFx32ToFx64_0203f278(fx32 a, fx32 b);

s64 SquareFx32ToFx64_0203f268(fx32 value)
{
    return MulFx32ToFx64_0203f278(value, value);
}
