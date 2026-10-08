#include "nitro/types.h"

typedef struct CommState {
    u8 pad_00[0x06];
    u16 flags;
    s8 slotIndex;
    u8 keepAudio : 1;
} CommState;

extern CommState *gContinueSceneState;
extern void StoreToGlobalPtr4Field28(int value);
extern int CacheSeqArcStatus(int index);
extern void CreateOv037Context(void);

s32 FinishCommSession(void)
{
    CommState *state = gContinueSceneState;
    u16 flags = state->flags | 0xc;

    state->flags = flags;
    if (flags & 1) {
        state->flags &= ~1;
    }
    if (state->keepAudio) {
        StoreToGlobalPtr4Field28(0);
        return 9;
    }
    CacheSeqArcStatus(2);
    CreateOv037Context();
    StoreToGlobalPtr4Field28(0);
    gContinueSceneState->flags |= 0x8000;
    return 3;
}
