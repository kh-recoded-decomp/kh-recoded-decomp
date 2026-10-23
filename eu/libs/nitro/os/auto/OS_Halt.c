/* NitroSDK original assembly (libraries/os/src/os_terminate_proc.c). */

#include "libs/nitro/os/os_types_internal.h"

void OS_Halt(void)
{
    __builtin_arm_mcr(15, 0, 0, 7, 0, 4);
}
