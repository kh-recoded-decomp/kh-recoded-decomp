#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
} OverlayState;

extern OverlayState *g_activeState_020bc800;

BOOL IsStopFlagClear_020bb55c(void)
{
    BOOL result = TRUE;
    if (g_activeState_020bc800->flags & 0x10) {
        result = FALSE;
    }
    return result;
}
