#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 timer;
    u8 pad_08[4];
    u32 flags;
} EntityState;

int func_0200cdc8(void *unused, EntityState *state)
{
    state->timer = 0;
    state->flags &= ~0x30;
    return 0;
}
