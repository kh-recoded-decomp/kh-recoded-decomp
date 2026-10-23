/* NitroSDK original assembly (libraries/os/src/os_system.c). */

typedef unsigned int OSProcMode;

#define HW_PSR_CPU_MODE_MASK 0x1f

OSProcMode OS_GetProcMode(void)
{
    return __builtin_arm_rsr("cpsr") & HW_PSR_CPU_MODE_MASK;
}
