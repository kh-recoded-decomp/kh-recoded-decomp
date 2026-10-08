#include "nitro/types.h"

extern u8 *data_ov001_020a0514;
extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, s32 value, u32 size);
extern u32 func_0202a768(void);
extern void ResetFieldCamera(void);

u32 CreateActorChannel(void)
{
    u8 *ctx;
    u32 heapHandle;

    ctx = NNSi_FndGetCurrentRootHeap();
    data_ov001_020a0514 = ctx;
    MI_CpuFill8(ctx, 0, 0x1f0);
    heapHandle = func_0202a768();
    *(u32 *)(ctx + 0x1d8) = heapHandle;
    ResetFieldCamera();
    return 0x208b7a5;
}
