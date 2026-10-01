#include "nitro/types.h"

typedef s32 (*SoundCtxStateFunc)(void);

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x0c];
    s32 state;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;
extern SoundCtxStateFunc g_ov038SoundCtxStates_020bbd98[];

u32 RunOv038SoundCtxStates_020ba468(void)
{
    s32 nextState;

    do {
        g_ov038SoundCtx_020bd140->flags &= 0x7fff;
        nextState = g_ov038SoundCtxStates_020bbd98[g_ov038SoundCtx_020bd140->state]();
        if (nextState >= 0) {
            g_ov038SoundCtx_020bd140->state = nextState;
        }
    } while (g_ov038SoundCtx_020bd140->flags & 0x8000);
    return 0;
}
