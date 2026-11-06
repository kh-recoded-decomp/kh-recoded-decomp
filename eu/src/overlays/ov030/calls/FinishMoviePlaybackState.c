#include "nitro/types.h"

typedef struct MoviePlaybackState {
    u8 pad_00[6];
    u16 flags;
} MoviePlaybackState;

extern MoviePlaybackState *gOv030SceneWork;

int FinishMoviePlaybackState(void)
{
    gOv030SceneWork->flags = gOv030SceneWork->flags & 0xfff3;
    return -1;
}
