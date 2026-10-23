#include "libs/nitro/os/os_types_internal.h"

void OS_SetProtectionRegion3(u32 parameter)
{
    __builtin_arm_mcr(15, 0, parameter, 6, 3, 0);
}
