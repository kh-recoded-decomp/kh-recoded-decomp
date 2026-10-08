#include "nitro/types.h"

typedef struct MoviePlaybackState {
    u8 pad_00[6];
    u16 flags;
} MoviePlaybackState;

extern MoviePlaybackState *data_ov030_020bd020;

int FinishMoviePlaybackState(void)
{
    data_ov030_020bd020->flags = data_ov030_020bd020->flags & 0xfff3;
    return -1;
}
