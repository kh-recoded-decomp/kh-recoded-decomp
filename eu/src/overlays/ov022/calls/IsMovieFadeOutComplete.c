#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[2232];
    s32 fadeStep;
} MovieScene;

extern MovieScene *gMovieSceneGlobals;

BOOL IsMovieFadeOutComplete(void)
{
    return gMovieSceneGlobals->fadeStep >= 16;
}
