#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} StateBuffer;

typedef struct {
    u8 pad_0000[0xCDFC];
    StateBuffer buffers[2];
    s32 bufferCount;
} Ov101State;

extern int FreeBufferAndClearStatus_0206a918(StateBuffer *buffer);

void ReleaseStateBuffers_020c06c0(Ov101State *state)
{
    int i;

    for (i = 0; i < state->bufferCount; i++) {
        FreeBufferAndClearStatus_0206a918(&state->buffers[i]);
    }
    state->bufferCount = 0;
}
