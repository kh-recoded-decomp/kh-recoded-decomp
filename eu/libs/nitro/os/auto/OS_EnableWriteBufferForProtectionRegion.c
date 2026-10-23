#include "libs/nitro/os/os_types_internal.h"

void OS_EnableWriteBufferForProtectionRegion(u32 flags)
{
    u32 regions = __builtin_arm_mrc(15, 0, 3, 0, 0);

    __builtin_arm_mcr(15, 0, regions | flags, 3, 0, 0);
}
