#include "nitro/types.h"

extern u8 *gActorChannelContext;
extern void *GetRunningTaskWork(void);
extern void MI_CpuFill8(void *dst, s32 value, u32 size);
extern u32 GetCurrentTaskObject(void);
extern void ResetFieldCamera(void);

u32 CreateActorChannel(void)
{
    u8 *ctx;
    u32 heapHandle;

    ctx = GetRunningTaskWork();
    gActorChannelContext = ctx;
    MI_CpuFill8(ctx, 0, 0x1f0);
    heapHandle = GetCurrentTaskObject();
    *(u32 *)(ctx + 0x1d8) = heapHandle;
    ResetFieldCamera();
    return 0x208b7a5;
}
