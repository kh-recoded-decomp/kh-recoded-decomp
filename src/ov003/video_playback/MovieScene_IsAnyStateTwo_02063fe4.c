#include "nitro/types.h"

typedef struct MovieScene {
    u8 pad_000[0x8b0];
    s32 streamState;
    s32 state;
} MovieScene;

extern MovieScene *NNSi_FndGetCurrentRootHeap_0202a764(void);

BOOL MovieScene_IsAnyStateTwo_02063fe4(void)
{
    MovieScene *scene = NNSi_FndGetCurrentRootHeap_0202a764();

    return scene->streamState == 2 || scene->state == 2;
}
