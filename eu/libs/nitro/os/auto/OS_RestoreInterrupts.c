/* NitroSDK original assembly (libraries/os/src/os_system.c). */
#include "libs/nitro/os/os_interrupt_state.h"

#define HW_PSR_IRQ_DISABLE 0x80u

OS_INTERRUPT_STATE_RESULT OSInterruptState OS_RestoreInterrupts(unsigned long state)
{
    unsigned previous = __builtin_arm_rsr("cpsr");
    unsigned updated = (previous & ~HW_PSR_IRQ_DISABLE) | state;
    OSInterruptState result;

    __builtin_arm_wsr("cpsr_c", updated);
    result.previousMask = previous & HW_PSR_IRQ_DISABLE;
    result.previousStatus = previous;
    result.updatedStatus = updated;
    return result;
}
