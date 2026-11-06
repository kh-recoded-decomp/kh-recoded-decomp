#include "nitro/types.h"

extern u32 gStageEventContext;
extern void ShutdownStageManagerIfActive(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void ClearQueueFlag(void);
extern void SetGlobalStateValue(s32 param);

void ResetStageEventContext(void)
{
    u8 *ctx;

    ctx = (u8 *)gStageEventContext;
    ShutdownStageManagerIfActive();
    ctx[0x108] = 0;
    MIi_CpuClearFast(0, ctx + 8, 0x100);
    ClearQueueFlag();
    SetGlobalStateValue(0);
}
