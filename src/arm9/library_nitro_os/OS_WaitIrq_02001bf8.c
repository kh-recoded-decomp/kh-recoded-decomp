#include "nitro/types.h"
#include "nitro/os.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void OS_SleepThread(void *queue);

extern u32 data_027e0000;
extern u32 data_027e00a0;

#define DTCM ((char *)&data_027e0000)

void OS_WaitIrq_02001bf8(BOOL clear, u32 irqFlags)
{
    OSIntrMode last = OS_DisableInterrupts();

    if (clear) {
        OSi_IrqCheckFlags &= ~irqFlags;
    }
    OS_RestoreInterrupts(last);

    {
        char *const dtcm = DTCM;

        if (irqFlags & *(volatile u32 *)(dtcm + 0x3ff8)) {
            return;
        }
        {
            volatile u32 *flags = (volatile u32 *)(dtcm + 0x3ff8);

            do {
                OS_SleepThread(&data_027e00a0);
            } while ((irqFlags & *flags) == 0);
        }
    }
}
