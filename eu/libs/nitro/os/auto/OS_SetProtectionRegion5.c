#include "libs/nitro/os/os_types_internal.h"

void OS_SetProtectionRegion5(u32 parameter)
{
    __builtin_arm_mcr(15, 0, parameter, 6, 5, 0);
}
