#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bd140;

BOOL IsOv038SoundCtxFlag0Clear_020ba620(void)
{
    if (g_ov038SoundCtx_020bd140 == NULL) {
        return FALSE;
    }
    if ((g_ov038SoundCtx_020bd140->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
