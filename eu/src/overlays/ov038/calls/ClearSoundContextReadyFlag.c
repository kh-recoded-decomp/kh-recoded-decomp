#include "nitro/types.h"

typedef struct SoundContextState {
    u8 pad_00[6];
    u16 flags;
} SoundContextState;

extern SoundContextState *gResultsPageOuterTaskWork;

u32 ClearSoundContextReadyFlag(void)
{
    SoundContextState *state = gResultsPageOuterTaskWork;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
