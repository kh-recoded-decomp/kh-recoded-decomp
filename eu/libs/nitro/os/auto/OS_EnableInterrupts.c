/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef unsigned int OSIntrMode;

#define HW_PSR_IRQ_DISABLE 0x80u

OSIntrMode OS_EnableInterrupts(void)
{
    OSIntrMode previous = __builtin_arm_rsr("cpsr");
    __builtin_arm_wsr("cpsr_c", previous & ~HW_PSR_IRQ_DISABLE);
    return previous & HW_PSR_IRQ_DISABLE;
}
