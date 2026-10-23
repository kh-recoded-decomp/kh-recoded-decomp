/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

#include "libs/nitro/os/os_types_internal.h"

#define HW_CACHE_LINE_SIZE 32u

void IC_InvalidateRange(u32 startAddress, u32 nBytes)
{
    u32 end = nBytes + startAddress;
    u32 line = startAddress & ~(HW_CACHE_LINE_SIZE - 1);

    /* The original loop visits at least one line and compares signed addresses. */
    do {
        __builtin_arm_mcr(15, 0, line, 7, 5, 1);
        line += HW_CACHE_LINE_SIZE;
    } while ((s32)line < (s32)end);
}
