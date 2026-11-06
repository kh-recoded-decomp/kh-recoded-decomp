#include "nitro/types.h"

typedef struct ScreenState {
    u8 pad_00[0x66];
    u8 flags;
} ScreenState;

extern ScreenState *gFieldScreenTransitionWork;

u32 SetScreenFlag1(void)
{
    ScreenState *state = gFieldScreenTransitionWork;
    u32 flags = state->flags;
    u32 result = (flags & ~1) | 1;

    state->flags = result;
    return result;
}
