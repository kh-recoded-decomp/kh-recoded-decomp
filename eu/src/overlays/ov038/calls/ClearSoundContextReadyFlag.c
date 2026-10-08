#include "nitro/types.h"

typedef struct SoundContextState {
    u8 pad_00[6];
    u16 flags;
} SoundContextState;

extern SoundContextState *data_ov038_020bd160;

u32 ClearSoundContextReadyFlag(void)
{
    SoundContextState *state = data_ov038_020bd160;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
