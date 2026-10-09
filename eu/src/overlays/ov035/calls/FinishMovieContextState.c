#include "nitro/types.h"

typedef struct MovieContextState {
    u8 pad_00[6];
    u16 flags;
} MovieContextState;

extern MovieContextState *gMovieContextState;

int FinishMovieContextState(void)
{
    gMovieContextState->flags = gMovieContextState->flags & 0xfff3;
    return -1;
}
