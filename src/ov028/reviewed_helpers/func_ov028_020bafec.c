#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020bb380;

BOOL func_ov028_020bafec(void)
{
    if (g_ov038SoundCtx_020bb380 == NULL) {
        return FALSE;
    }
    if ((g_ov038SoundCtx_020bb380->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
