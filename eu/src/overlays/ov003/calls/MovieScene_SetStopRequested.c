#include "nitro/types.h"

typedef struct MovieSceneState {
    u8 pad_000[0x8b9];
    u8 stopRequested;
} MovieSceneState;

extern MovieSceneState *data_ov003_020658c0;

void MovieScene_SetStopRequested(void)
{
    data_ov003_020658c0->stopRequested = TRUE;
}
