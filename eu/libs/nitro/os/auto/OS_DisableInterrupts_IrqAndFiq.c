/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef unsigned int OSIntrMode;

#define HW_PSR_IRQ_FIQ_DISABLE 0xc0u

OSIntrMode OS_DisableInterrupts_IrqAndFiq(void)
{
    OSIntrMode previous = __builtin_arm_rsr("cpsr");
    __builtin_arm_wsr("cpsr_c", previous | HW_PSR_IRQ_FIQ_DISABLE);
    return previous & HW_PSR_IRQ_FIQ_DISABLE;
}
