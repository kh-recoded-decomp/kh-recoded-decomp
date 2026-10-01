#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ModeLayer;

typedef struct {
    s32 layerCount;
    u8 pad_04[4];
    void **buffers;
    u8 pad_0c[4];
    ModeLayer *layers;
} ModeLayerSet;

typedef struct {
    u8 pad_00[0x38];
    void *workBuffer;
    u8 pad_3c[0x18];
    ModeLayerSet layerSet;
    u8 pad_68[0x2c];
    ModeLayer mainLayer;
} ModeState;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void FreeModeLayerArray_020793e4(ModeState *state);

void FreeModeResources_0207942c(ModeState *state)
{
    int index;
    ModeLayerSet *set = &state->layerSet;

    if (state->workBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state->workBuffer);
        state->workBuffer = NULL;
        CallVirtualHandlerSlot1_02001574(&state->mainLayer, 0);
        FlushBufferAndRunCallback_0200153c(&state->mainLayer);
        DestroyFndObjectList_020014f0(&state->mainLayer);
    }
    if (set->buffers != NULL) {
        for (index = 0; index < set->layerCount; index++) {
            if (set->buffers[index] != NULL) {
                NNSi_FndFreeFromDefaultHeap_0202a1c4(set->buffers[index]);
            }
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(set->buffers);
        set->buffers = NULL;
    }
    FreeModeLayerArray_020793e4(state);
}
