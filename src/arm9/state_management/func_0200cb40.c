#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 timer;
    u8 pad_08[4];
    u32 flags;
} EntityState;

extern int func_0200c6fc(EntityState *state, u32 arg1, u32 arg2);

int func_0200cb40(void *unused, EntityState *state)
{
    int result = func_0200c6fc(state, 8, 1);
    state->timer = 0;
    state->flags &= ~0x30;
    return result;
}
