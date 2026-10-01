#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020baba0;

BOOL func_ov029_020ba9d4(void)
{
    if (g_ov038SoundCtx_020baba0 == NULL) {
        return FALSE;
    }
    if ((g_ov038SoundCtx_020baba0->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
