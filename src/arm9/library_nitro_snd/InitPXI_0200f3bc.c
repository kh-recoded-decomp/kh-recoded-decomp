#include "nitro/types.h"

#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

extern void PXI_SetFifoRecvCallback_0200e29c(u32 fifoTag, void *callback);
extern BOOL PXI_IsCallbackReady_0200e2e8(u32 fifoTag, int proc);
extern int CheckCommandProcessorReady_0200f490(void);
extern void Sound_DispatchAlarmWithInterruptsDisabled_0200f398(int tag, int data);
extern void func_020049b4(u32 cycles);

void InitPXI_0200f3bc(void)
{
    PXI_SetFifoRecvCallback_0200e29c(PXI_FIFO_TAG_SOUND, Sound_DispatchAlarmWithInterruptsDisabled_0200f398);

    if (CheckCommandProcessorReady_0200f490()) {
        while (!PXI_IsCallbackReady_0200e2e8(PXI_FIFO_TAG_SOUND, PXI_PROC_ARM7)) {
            func_020049b4(50);
        }
    }
}
