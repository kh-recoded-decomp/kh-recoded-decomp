#include "nitro/types.h"

typedef struct SoundCtx {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;

s32 MarkSoundCtxRepeatIfReady_020ba58c(void)
{
    SoundCtx *ctx = g_ov038SoundCtx_020bd140;

    if (ctx->flags & 0x4000) {
        ctx->flags |= 0x8000;
        return 4;
    }
    return -1;
}
