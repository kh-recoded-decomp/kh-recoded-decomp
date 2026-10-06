#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *gContinueSceneState;

BOOL func_ov037_020babbc(void)
{
    if (gContinueSceneState == NULL) {
        return FALSE;
    }
    if ((gContinueSceneState->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
