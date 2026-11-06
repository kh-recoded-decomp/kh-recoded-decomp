#include "nitro/types.h"

typedef struct ResumeModeState {
    u8 pad_00[6];
    u16 flags;
} ResumeModeState;

extern ResumeModeState *gResumeModeWorkStorage;

u32 ClearResumeModeReadyFlag(void)
{
    ResumeModeState *state = gResumeModeWorkStorage;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
