/* NitroSDK original assembly (libraries/os/src/os_protectionRegion.c). */

#include "libs/nitro/os/os_types_internal.h"

void OS_SetProtectionRegion1(u32 parameter)
{
    __builtin_arm_mcr(15, 0, parameter, 6, 1, 0);
}
