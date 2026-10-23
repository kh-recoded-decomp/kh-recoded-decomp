/* NitroSDK original assembly (libraries/os/src/os_tcm.c). */

#include "libs/nitro/os/os_types_internal.h"

#define OSi_TCM_REGION_BASE_MASK 0xfffff000u

u32 OS_GetDTCMAddress(void)
{
    return __builtin_arm_mrc(15, 0, 9, 1, 0) & OSi_TCM_REGION_BASE_MASK;
}
