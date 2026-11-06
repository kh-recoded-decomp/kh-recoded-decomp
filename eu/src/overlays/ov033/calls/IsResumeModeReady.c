#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} SoundCtx;

extern SoundCtx *gResumeModeWorkStorage;

BOOL IsResumeModeReady(void)
{
    if (gResumeModeWorkStorage == NULL) {
        return FALSE;
    }
    if ((gResumeModeWorkStorage->flags & 1) == 0) {
        return TRUE;
    }
    return FALSE;
}
