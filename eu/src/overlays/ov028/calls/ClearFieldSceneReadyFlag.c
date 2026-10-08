#include "nitro/types.h"

typedef struct FieldSceneState {
    u8 pad_00[6];
    u16 flags;
} FieldSceneState;

extern FieldSceneState *data_ov028_020bb3a0;

u32 ClearFieldSceneReadyFlag(void)
{
    FieldSceneState *state = data_ov028_020bb3a0;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
