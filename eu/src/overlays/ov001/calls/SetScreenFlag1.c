#include "nitro/types.h"

typedef struct ScreenState {
    u8 pad_00[0x66];
    u8 flags;
} ScreenState;

extern ScreenState *data_ov001_020a04a0;

u32 SetScreenFlag1(void)
{
    ScreenState *state = data_ov001_020a04a0;
    u32 flags = state->flags;
    u32 result = (flags & ~1) | 1;

    state->flags = result;
    return result;
}
