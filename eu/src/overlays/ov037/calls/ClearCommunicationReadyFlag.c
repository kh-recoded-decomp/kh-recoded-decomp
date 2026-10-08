#include "nitro/types.h"

typedef struct CommunicationState {
    u8 pad_00[6];
    u16 flags;
} CommunicationState;

extern CommunicationState *gContinueSceneState;

u32 ClearCommunicationReadyFlag(void)
{
    CommunicationState *state = gContinueSceneState;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
