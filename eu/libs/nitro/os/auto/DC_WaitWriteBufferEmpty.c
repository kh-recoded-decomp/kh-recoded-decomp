/* NitroSDK original assembly (libraries/os/src/os_cache.c). */

#include "libs/nitro/os/os_types_internal.h"

void DC_WaitWriteBufferEmpty(void)
{
    __builtin_arm_mcr(15, 0, 0, 7, 10, 4);
}
