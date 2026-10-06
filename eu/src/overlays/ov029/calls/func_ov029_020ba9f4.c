#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *data_ov029_020babc0;

BOOL func_ov029_020ba9f4(void)
{
    if (data_ov029_020babc0 == NULL) {
        return FALSE;
    }
    if ((data_ov029_020babc0->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
