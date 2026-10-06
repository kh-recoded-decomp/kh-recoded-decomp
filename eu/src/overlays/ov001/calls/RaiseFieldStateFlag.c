#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_00[0x11];
    u8 flags;
} FieldState;

extern FieldState *data_ov001_020a0498;

void RaiseFieldStateFlag(void)
{
    FieldState *state = data_ov001_020a0498;

    if (!(state->flags & 1)) {
        state->flags = 1;
    }
}
