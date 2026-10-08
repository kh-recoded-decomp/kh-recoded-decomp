#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} StateBuffer;

typedef struct {
    u8 pad_0000[0xCE04];
    StateBuffer buffers[2];
    s32 bufferCount;
} Ov101State;

extern int func_ov001_0206a918(StateBuffer *buffer);

void ReleaseStateBuffers(Ov101State *state)
{
    int i;

    for (i = 0; i < state->bufferCount; i++) {
        func_ov001_0206a918(&state->buffers[i]);
    }
    state->bufferCount = 0;
}

