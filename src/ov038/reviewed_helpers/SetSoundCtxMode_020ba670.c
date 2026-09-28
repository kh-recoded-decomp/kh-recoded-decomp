#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
    u8 mode;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;

void SetSoundCtxMode_020ba670(u8 mode)
{
    g_ov038SoundCtx_020bd140->mode = mode;
    g_ov038SoundCtx_020bd140->flags = g_ov038SoundCtx_020bd140->flags | 0x4000;
}
