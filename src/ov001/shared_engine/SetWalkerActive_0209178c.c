#include "nitro/types.h"

typedef struct StageWalker {
    u8 pad_000[0x12a];
    u16 displayFlags;
    u8 pad_12C[0x15c];
    u16 lowFlags : 4;
    u16 isActive : 1;
    u16 highFlags : 11;
} StageWalker;

void SetWalkerActive_0209178c(StageWalker *walker, BOOL active)
{
    BOOL enabled = TRUE;

    if (!active) {
        enabled = FALSE;
    }
    walker->isActive = (u16)enabled;
    if (!walker->isActive) {
        walker->displayFlags |= 0x80;
        return;
    }
    walker->displayFlags &= 0xff7f;
}
