#include "nitro/types.h"

typedef struct MoviePlayerState {
    u8 pad_00[6];
    u16 flags;
} MoviePlayerState;

extern MoviePlayerState *gOv031SceneWorkStorage;

int FinishMoviePlayerState(void)
{
    gOv031SceneWorkStorage->flags = gOv031SceneWorkStorage->flags & 0xfff3;
    return -1;
}
