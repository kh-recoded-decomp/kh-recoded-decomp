#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ModeLayer;

typedef struct {
    s32 layerCount;
    u8 pad_04[0xc];
    ModeLayer *layers;
} ModeLayerSet;

typedef struct {
    u8 pad_00[0x54];
    ModeLayerSet layerSet;
} ModeState;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeModeLayerArray_020793e4(ModeState *state)
{
    ModeLayerSet *set = &state->layerSet;

    if (set->layers != NULL) {
        int index;

        for (index = 0; index < set->layerCount; index++) {
            ModeLayer *layers = set->layers;

            CallVirtualHandlerSlot1_02001574(&layers[index], 0);
            FlushBufferAndRunCallback_0200153c(&layers[index]);
            DestroyFndObjectList_020014f0(&layers[index]);
        }
        NNSi_FndFreeFromDefaultHeap_0202a1c4(set->layers);
        set->layers = NULL;
        set->layerCount = 0;
    }
}
