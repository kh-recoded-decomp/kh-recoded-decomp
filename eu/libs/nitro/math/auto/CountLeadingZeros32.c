#include "nitro/types.h"

int CountLeadingZeros32(u32 value)
{
    /* The ARM CLZ instruction defines the zero input as 32. */
    return value ? __builtin_clz(value) : 32;
}
