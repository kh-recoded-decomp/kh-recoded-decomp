#include "nitro/types.h"

extern u8 *g_channelContext_020a04f4;
extern void func_0203a970(void *channel);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void func_01ff8830(void *dst, s32 value, u32 size);
extern void func_0203a930(void *channel, u32 value);
extern void func_0203ab94(void *channel, u32 value);
extern void func_0203ac1c(void *channel, u32 value);
extern void func_0203ac20(void *channel, u32 value);

void ActorChannel_ConfigureAndPlay_0208b9cc(u32 channelId, u32 param2, s32 resetMode)
{
    u8 *ctx;
    u32 state;
    u8 saveBuffer[56];

    ctx = g_channelContext_020a04f4;
    func_0203a970(ctx + 0x140);
    if (resetMode == 0) {
        func_01ff8ad8(ctx, saveBuffer, 0x38);
        func_01ff8830(ctx + 0x38, 0, 0xa0);
        func_01ff8ad8(saveBuffer, ctx, 0x38);
        state = 1;
    } else {
        func_01ff8830(ctx + 0x140, 0, 0x5c);
        if (1 < *(s32 *)(ctx + 0x98) + 1U) goto skipState;
        state = 2;
    }
    *(u32 *)(ctx + 0x98) = state;
skipState:
    func_0203a930(ctx + 0x140,
                  (*(s32 *)(ctx + 0x1d4) + 0x8000U & 0xfffffc) << 7 | 0x80000000 |
                  channelId & 0x1ff);
    func_0203ab94(ctx + 0x140, 0);
    func_0203ac1c(ctx + 0x140, param2);
    func_0203ac20(ctx + 0x140, 0x1000);
    *(u32 *)(ctx + 0x9c) = 0xffffffff;
    *(s32 *)(ctx + 0x1e4) = resetMode;
}
