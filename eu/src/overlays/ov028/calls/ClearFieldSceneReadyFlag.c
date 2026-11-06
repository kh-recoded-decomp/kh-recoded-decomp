#include "nitro/types.h"

typedef struct FieldSceneState {
    u8 pad_00[6];
    u16 flags;
} FieldSceneState;

extern FieldSceneState *gOv028FieldSceneWorkStorage;

u32 ClearFieldSceneReadyFlag(void)
{
    FieldSceneState *state = gOv028FieldSceneWorkStorage;
    u32 flags = state->flags & 0xfffd;
    state->flags = flags;
    return flags;
}
