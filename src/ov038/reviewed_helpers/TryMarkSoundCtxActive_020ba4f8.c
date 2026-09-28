#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;
extern u32 func_ov001_02063620(void);

u32 TryMarkSoundCtxActive_020ba4f8(void)
{
    u32 result;

    result = func_ov001_02063620();
    if (result == 0) {
        g_ov038SoundCtx_020bd140->flags = g_ov038SoundCtx_020bd140->flags | 0x8000;
        return 1;
    }
    return 0xffffffff;
}
