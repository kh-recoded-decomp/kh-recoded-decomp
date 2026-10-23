#include "libs/nitro/os/os_types_internal.h"

void OS_DisableICacheForProtectionRegion(u32 flags)
{
    u32 regions = __builtin_arm_mrc(15, 0, 2, 0, 1);

    __builtin_arm_mcr(15, 0, regions & ~flags, 2, 0, 1);
}
