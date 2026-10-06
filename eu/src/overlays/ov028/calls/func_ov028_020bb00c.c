#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov028_020bb3a0;

BOOL func_ov028_020bb00c(void)
{
    if (data_ov028_020bb3a0 == NULL) {
        return FALSE;
    }
    if ((data_ov028_020bb3a0->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
