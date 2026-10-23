/* NitroSDK original assembly (libraries/os/src/os_protectionUnit.c). */

#include "libs/nitro/os/os_types_internal.h"

#define HW_C1_PROTECT_UNIT_ENABLE 0x00000001

void OS_EnableProtectionUnit(void)
{
    u32 control = __builtin_arm_mrc(15, 0, 1, 0, 0);

    __builtin_arm_mcr(15, 0, control | HW_C1_PROTECT_UNIT_ENABLE, 1, 0, 0);
}
