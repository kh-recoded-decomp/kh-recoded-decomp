/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef unsigned int OSIntrMode_Irq;

#define HW_PSR_IRQ_DISABLE 0x80

OSIntrMode_Irq OS_GetCpsrIrq(void)
{
    return __builtin_arm_rsr("cpsr") & HW_PSR_IRQ_DISABLE;
}
