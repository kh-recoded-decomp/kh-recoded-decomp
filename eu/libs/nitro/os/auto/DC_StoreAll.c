/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

#include "libs/nitro/os/os_types_internal.h"

#define HW_C7_CACHE_SET_NO_SHIFT 30
#define HW_CACHE_LINE_SIZE 32
#define HW_DCACHE_SIZE 0x1000

u32 DC_StoreAll(void)
{
    u32 set = 0;
    u32 offset;

    do {
        offset = 0;
        do {
            u32 line = set | offset;
            __builtin_arm_mcr(15, 0, line, 7, 10, 2);
            offset += HW_CACHE_LINE_SIZE;
        } while ((s32)offset < HW_DCACHE_SIZE / 4);
        set += 1u << HW_C7_CACHE_SET_NO_SHIFT;
    } while (set != 0);

    /* The original routine leaves the final per-set offset in r0. */
    return offset;
}
