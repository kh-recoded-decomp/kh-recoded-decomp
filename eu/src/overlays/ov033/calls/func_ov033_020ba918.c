#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov033_020baae0;

BOOL func_ov033_020ba918(void)
{
    if (data_ov033_020baae0 == NULL) {
        return FALSE;
    }
    if ((data_ov033_020baae0->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
