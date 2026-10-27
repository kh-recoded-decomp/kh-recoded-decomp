#include "nitro/types.h"

s32 MI_SwapWord(s32 value, volatile s32 *address)
{
    return (s32)__swp((u32)value, address);
}
