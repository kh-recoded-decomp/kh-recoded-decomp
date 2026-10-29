#include "nitro/types.h"

extern u8 SDK_AUTOLOAD_DTCM_START[];

/* Masks load into r1 from the literal pool. */
register u32 sMask __asm("r1");

void func_02000a78(void)
{
    u32 value;

    value = __builtin_arm_mrc(15, 0, 1, 0, 0);
    sMask = 0x000f9005;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    value &= ~sMask;
    __builtin_arm_mcr(15, 0, value, 1, 0, 0);
    value = 0;
    __builtin_arm_mcr(15, 0, value, 7, 5, 0);
    __builtin_arm_mcr(15, 0, value, 7, 6, 0);
    __builtin_arm_mcr(15, 0, value, 7, 10, 4);
    __builtin_arm_mcr(15, 0, 0x04000033, 6, 0, 0);
    __builtin_arm_mcr(15, 0, 0x02000031, 6, 1, 0);
    __builtin_arm_mcr(15, 0, 0x027ff017, 6, 2, 0);
    __builtin_arm_mcr(15, 0, 0x08000035, 6, 3, 0);
    {
        register u32 region __asm("r0");

        region = (u32)SDK_AUTOLOAD_DTCM_START;
        region |= 0x1a;
        region |= 1;
        __builtin_arm_mcr(15, 0, region, 6, 4, 0);
    }
    __builtin_arm_mcr(15, 0, 0x0100002f, 6, 5, 0);
    __builtin_arm_mcr(15, 0, 0xffff001d, 6, 6, 0);
    __builtin_arm_mcr(15, 0, 0x02fff017, 6, 7, 0);
    __builtin_arm_mcr(15, 0, 0x20, 9, 1, 1);
    value = (u32)SDK_AUTOLOAD_DTCM_START;
    value |= 0xa;
    __builtin_arm_mcr(15, 0, value, 9, 1, 0);
    __builtin_arm_mcr(15, 0, 0x4a, 2, 0, 1);
    __builtin_arm_mcr(15, 0, 0x4a, 2, 0, 0);
    __builtin_arm_mcr(15, 0, 0xa, 3, 0, 0);
    __builtin_arm_mcr(15, 0, 0x05101011, 5, 0, 3);
    __builtin_arm_mcr(15, 0, 0x15111111, 5, 0, 2);
    value = __builtin_arm_mrc(15, 0, 1, 0, 0);
    sMask = 0x0005707d;
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
    value |= sMask;
    __builtin_arm_mcr(15, 0, value, 1, 0, 0);
}
