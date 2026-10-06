#include "nitro/types.h"

typedef s32 (*SoundCtxStateFunc)(void);

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 pad_08[0x0c];
    s32 state;
} SoundCtx;

extern SoundCtx *data_ov033_020baae0;
extern SoundCtxStateFunc gResumeModeHandlers[];

u32 func_ov033_020ba574(void)
{
    s32 nextState;

    do {
        data_ov033_020baae0->flags &= 0x7fff;
        nextState = gResumeModeHandlers[data_ov033_020baae0->state]();
        if (nextState >= 0) {
            data_ov033_020baae0->state = nextState;
        }
    } while (data_ov033_020baae0->flags & 0x8000);
    return 0;
}
