#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 data[0xc];
} PackedFileView;

typedef struct {
    u8 pad_0000[0x18];
    u8 font[0xC];
    TextLayer layers[4];
    u8 pad_00F4[0xCB64 - 0xF4];
    PackedFileView views[3];
} Ov103State;

extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern BOOL DestroyFndObjectList_020014f0(TextLayer *layer);
extern void FreePointerIfSet_020ba294(PackedFileView *view);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(void *resource);

void FreeTextLayers_020bf32c(Ov103State *state)
{
    int i;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1_02001574(&state->layers[i], 0);
        FlushBufferAndRunCallback_0200153c(&state->layers[i]);
        DestroyFndObjectList_020014f0(&state->layers[i]);
    }
    for (i = 0; i < 3; i++) {
        FreePointerIfSet_020ba294(&state->views[i]);
    }
    FreeResourceBufferAndProbeHeap_02001474(state->font);
}
