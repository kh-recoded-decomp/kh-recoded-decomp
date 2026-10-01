#include "nitro/types.h"

typedef struct ScreenState {
    u32 flags;
} ScreenState;

extern ScreenState *data_ov001_020a0480;

BOOL IsScreenModeIdle_0206a814(void)
{
    ScreenState *screen = data_ov001_020a0480;

    if (screen == NULL) {
        return TRUE;
    }
    if (!(screen->flags & 0xf)) {
        return TRUE;
    }
    return FALSE;
}
