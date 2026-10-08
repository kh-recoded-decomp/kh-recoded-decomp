#include "nitro/types.h"

typedef struct CommunicationState {
    u8 pad_00[6];
    u16 flags;
} CommunicationState;

extern CommunicationState *gContinueSceneState;

int FinishCommunicationState(void)
{
    gContinueSceneState->flags = gContinueSceneState->flags & 0xfff3;
    return -1;
}
