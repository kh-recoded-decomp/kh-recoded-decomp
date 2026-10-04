#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} HandlerSlot;

typedef struct {
    void *data;
    u8 pad_04[8];
} PointerSlot;

typedef struct {
    u8 pad_0000[0x30];
    u8 resource[0xC];
    HandlerSlot handlers[4];
    u8 pad_010C[0xCFA0 - 0x10C];
    PointerSlot pointers[3];
} Ov101State;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void FreePointerIfSet_020ba294(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(void *resource);

void ShutdownStateHandlers_020bf5c4(Ov101State *state)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1_02001574(&state->handlers[i], 0);
        FlushBufferAndRunCallback_0200153c(&state->handlers[i]);
        DestroyFndObjectList_020014f0(&state->handlers[i]);
    }
    for (j = 0; j < 3; j++) {
        FreePointerIfSet_020ba294(&state->pointers[j]);
    }
    FreeResourceBufferAndProbeHeap_02001474(state->resource);
}
