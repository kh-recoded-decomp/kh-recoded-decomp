#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *g_ov038SoundCtx_020baac0;

BOOL func_ov033_020ba8f8(void)
{
    if (g_ov038SoundCtx_020baac0 == NULL) {
        return FALSE;
    }
    if ((g_ov038SoundCtx_020baac0->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
