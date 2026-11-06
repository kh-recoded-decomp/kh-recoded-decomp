/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern void *StartTimerState(void);

extern void *GetRunningTaskWork(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern u32 gSessionTimerWork;

u32 SubScene9_Create_02068c0c(u32 *cfg)
{
    u32 *state;

    state = (u32 *)GetRunningTaskWork();
    gSessionTimerWork = (u32)state;
    MIi_CpuClearFast(0, state, 0x2c);
    *state = *cfg;
    *(u16 *)((u8 *)state + 0x22) = 0x1000;
    return (u32)StartTimerState;
}
