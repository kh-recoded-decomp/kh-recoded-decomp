#include "nitro/types.h"

typedef struct MovieSceneState {
    u8 pad_000[0x8b9];
    u8 stopRequested;
} MovieSceneState;

extern MovieSceneState *gMovieSceneWork;

void MovieScene_SetStopRequested(void)
{
    gMovieSceneWork->stopRequested = TRUE;
}
