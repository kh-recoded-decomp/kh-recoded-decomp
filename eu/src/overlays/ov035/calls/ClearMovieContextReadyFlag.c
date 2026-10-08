#include "nitro/types.h"

typedef struct MovieContextState {
    u8 pad_00[6];
    u16 flags;
} MovieContextState;

extern MovieContextState *data_ov035_020bc500;

u32 ClearMovieContextReadyFlag(void)
{
    MovieContextState *state = data_ov035_020bc500;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
