/* NitroSDK original assembly (libraries/os/src/os_protectionRegion.c). */

#include "libs/nitro/os/os_types_internal.h"

void OS_SetDPermissionsForProtectionRegion(u32 setMask, u32 flags)
{
    u32 permissions = __builtin_arm_mrc(15, 0, 5, 0, 2);

    __builtin_arm_mcr(15, 0, (permissions & ~setMask) | flags, 5, 0, 2);
}
