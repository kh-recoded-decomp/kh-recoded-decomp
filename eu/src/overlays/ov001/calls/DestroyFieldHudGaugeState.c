#include "nitro/types.h"

typedef struct GaugeGraphicsState {
    void *buffers[3];
    void *packed[3];
    void *frameBuffer;
    void *framePacked;
    void *palette;
    u32 reserved24;
    s32 soundPlaying;
} GaugeGraphicsState;

extern GaugeGraphicsState *data_ov001_020a04cc;
extern void NNSi_FndFreeFromDefaultHeap(void *buffer);

void DestroyFieldHudGaugeState(void)
{
    GaugeGraphicsState *state = data_ov001_020a04cc;
    s32 index;

    if (state->frameBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(state->frameBuffer);
    }
    if (state->framePacked != NULL) {
        NNSi_FndFreeFromDefaultHeap(state->framePacked);
    }
    if (state->palette != NULL) {
        NNSi_FndFreeFromDefaultHeap(state->palette);
    }
    index = 0;
    do {
        if (state->buffers[index] != NULL) {
            NNSi_FndFreeFromDefaultHeap(state->buffers[index]);
        }
        if (state->packed[index] != NULL) {
            NNSi_FndFreeFromDefaultHeap(state->packed[index]);
        }
        index = index + 1;
    } while (index < 3);
    state->soundPlaying = 0;
    data_ov001_020a04cc = NULL;
}
