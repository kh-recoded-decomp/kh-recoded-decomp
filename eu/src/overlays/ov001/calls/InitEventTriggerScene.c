/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern u32 WaitForEventTriggerActivation(void);

extern void *GetRunningTaskWork(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void MIi_CpuClear16(u32 value, void *dest, u32 size);
extern u32 NNSi_FndAllocFromDefaultHeap(u32 size);
extern u32 gFieldTaskManagerWork;

u32 InitEventTriggerScene(void)
{
    u32 ctx;
    u32 block;

    ctx = (u32)GetRunningTaskWork();
    gFieldTaskManagerWork = ctx;
    MIi_CpuClearFast(0, (void *)ctx, 0x38);
    *(u8 *)(ctx + 0x11) = 0;
    MIi_CpuClear16(0xffff, (void *)ctx, 0x10);
    block = NNSi_FndAllocFromDefaultHeap(0x54);
    *(u32 *)(ctx + 0x34) = block;
    MIi_CpuClearFast(0, (void *)block, 0x54);
    *(u16 *)(*(u32 *)(ctx + 0x34) + 0x50) = 0xffff;
    return (u32)WaitForEventTriggerActivation;
}
