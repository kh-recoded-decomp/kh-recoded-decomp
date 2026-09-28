#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1C];
    void *buffers[5];
} Ov101State;

extern int ZeroHalfThenFree_0202cd78(void *block);

void FreeStateBuffers_020bf290(Ov101State *state)
{
    int i;

    for (i = 0; i < 5; i++) {
        ZeroHalfThenFree_0202cd78(state->buffers[i]);
    }
}
