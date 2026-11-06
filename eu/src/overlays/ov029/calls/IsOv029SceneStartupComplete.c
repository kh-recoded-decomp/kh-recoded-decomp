#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *gOv029SceneWorkStorage;

BOOL IsOv029SceneStartupComplete(void)
{
    if (gOv029SceneWorkStorage == NULL) {
        return FALSE;
    }
    if ((gOv029SceneWorkStorage->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
