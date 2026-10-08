#include "nitro/types.h"

typedef struct MoviePlayerState {
    u8 pad_00[6];
    u16 flags;
} MoviePlayerState;

extern MoviePlayerState *data_ov031_020bc820;

u32 ClearMovieSourceReadyFlag(void)
{
    MoviePlayerState *state = data_ov031_020bc820;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
