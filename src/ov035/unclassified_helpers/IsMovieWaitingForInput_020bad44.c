#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[6];
    u16 flags;
    u8 pad_08[0x1e];
    s16 pendingInput;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;

BOOL IsMovieWaitingForInput_020bad44(void)
{
    BOOL waiting = TRUE;

    if (g_movieContext_020bc4e0->flags & 0x10) {
        waiting = FALSE;
    }
    if (g_movieContext_020bc4e0->pendingInput >= 0) {
        waiting = FALSE;
    }
    return waiting;
}