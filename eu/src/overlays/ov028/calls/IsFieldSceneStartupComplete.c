#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *gOv028FieldSceneWorkStorage;

BOOL IsFieldSceneStartupComplete(void)
{
    if (gOv028FieldSceneWorkStorage == NULL) {
        return FALSE;
    }
    if ((gOv028FieldSceneWorkStorage->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
