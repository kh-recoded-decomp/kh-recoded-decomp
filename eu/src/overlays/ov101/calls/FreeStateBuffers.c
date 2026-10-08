#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x24];
    void *buffers[5];
} Ov101State;

extern int ZeroHalfThenFree(void *block);

void FreeStateBuffers(Ov101State *state)
{
    int i;

    for (i = 0; i < 5; i++) {
        ZeroHalfThenFree(state->buffers[i]);
    }
}
