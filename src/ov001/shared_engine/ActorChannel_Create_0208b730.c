#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;
extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8830(void *dst, s32 value, u32 size);
extern u32 func_0202a754(void);
extern void func_ov001_0208ae68(void);

u32 ActorChannel_Create_0208b730(void)
{
    u8 *ctx;
    u32 heapHandle;

    ctx = NNSi_FndGetCurrentRootHeap_0202a764();
    g_channelContext_020a04f4 = ctx;
    func_01ff8830(ctx, 0, 0x1f0);
    heapHandle = func_0202a754();
    *(u32 *)(ctx + 0x1d8) = heapHandle;
    func_ov001_0208ae68();
    return 0x208b77d;
}
