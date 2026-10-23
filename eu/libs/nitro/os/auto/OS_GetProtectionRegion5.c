#include "libs/nitro/os/os_types_internal.h"

u32 OS_GetProtectionRegion5(void)
{
    return __builtin_arm_mrc(15, 0, 6, 5, 0);
}
