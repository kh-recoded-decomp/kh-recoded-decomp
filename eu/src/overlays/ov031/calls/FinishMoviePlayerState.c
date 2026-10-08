#include "nitro/types.h"

typedef struct MoviePlayerState {
    u8 pad_00[6];
    u16 flags;
} MoviePlayerState;

extern MoviePlayerState *data_ov031_020bc820;

int FinishMoviePlayerState(void)
{
    data_ov031_020bc820->flags = data_ov031_020bc820->flags & 0xfff3;
    return -1;
}
