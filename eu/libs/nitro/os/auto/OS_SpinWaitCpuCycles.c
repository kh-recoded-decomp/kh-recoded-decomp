#include "libs/nitro/os/os_types_internal.h"

void OS_SpinWaitCpuCycles(u32 cycles)
{
    /* Stop on the first subtraction that borrows, including a zero input. */
    while (!__builtin_usub_overflow(cycles, 4u, &cycles)) {
    }
}
