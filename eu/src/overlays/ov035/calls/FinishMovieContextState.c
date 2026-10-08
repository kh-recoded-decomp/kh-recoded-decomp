#include "nitro/types.h"

typedef struct MovieContextState {
    u8 pad_00[6];
    u16 flags;
} MovieContextState;

extern MovieContextState *data_ov035_020bc500;

int FinishMovieContextState(void)
{
    data_ov035_020bc500->flags = data_ov035_020bc500->flags & 0xfff3;
    return -1;
}
