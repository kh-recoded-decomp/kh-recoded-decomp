#include "nitro/types.h"

typedef struct FieldState {
    u8 pad_00[0x11];
    u8 flags;
} FieldState;

extern FieldState *gFieldTaskManagerWork;

void RaiseFieldStateFlag(void)
{
    FieldState *state = gFieldTaskManagerWork;

    if (!(state->flags & 1)) {
        state->flags = 1;
    }
}
