#include "nitro/types.h"

u32 OS_CountZeroBits_02004b64(u32 value)
{
    asm {
        clz value, value
    }
    return value;
}
