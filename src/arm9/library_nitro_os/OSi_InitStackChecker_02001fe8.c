#include "nitro/types.h"

extern unsigned char data_027e0000[];
extern void SDK_IRQ_STACKSIZE(void);

#define HW_DTCM_IRQ_STACK_END           ((u32)data_027e0000 + 0x3f80)
#define OSi_IRQ_STACK_BOTTOM            HW_DTCM_IRQ_STACK_END
#define OSi_IRQ_STACK_TOP               (OSi_IRQ_STACK_BOTTOM - (u32)SDK_IRQ_STACKSIZE)
#define OSi_IRQ_STACK_CHECKNUM_BOTTOM   0xfddb597dUL
#define OSi_IRQ_STACK_CHECKNUM_TOP      0x7bf9dd5bUL

void OSi_InitStackChecker_02001fe8(void)
{

    *(u32 *)(OSi_IRQ_STACK_BOTTOM - 4) = OSi_IRQ_STACK_CHECKNUM_BOTTOM;
    *(u32 *)(OSi_IRQ_STACK_TOP) = OSi_IRQ_STACK_CHECKNUM_TOP;
}
