#include "libs/nitro/os/os_types_internal.h"

u32 OS_GetProtectionRegion2(void)
{
    return __builtin_arm_mrc(15, 0, 6, 2, 0);
}
