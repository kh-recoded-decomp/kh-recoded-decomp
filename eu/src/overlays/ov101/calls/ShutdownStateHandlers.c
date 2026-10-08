#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} HandlerSlot;

typedef struct {
    void *data;
    u8 pad_04[8];
} PointerSlot;

typedef struct {
    u8 pad_0000[0x38];
    u8 resource[0xC];
    HandlerSlot handlers[4];
    u8 pad_0114[0xCFA8 - 0x114];
    PointerSlot pointers[4];
} Ov101State;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void FlushBufferAndRunCallback(void *context);
extern BOOL DestroyFndObjectList(void *container);
extern void FreePointerIfSet(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap(void *resource);

void ShutdownStateHandlers(Ov101State *state)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1(&state->handlers[i], 0);
        FlushBufferAndRunCallback(&state->handlers[i]);
        DestroyFndObjectList(&state->handlers[i]);
    }
    for (j = 0; j < 4; j++) {
        FreePointerIfSet(&state->pointers[j]);
    }
    FreeResourceBufferAndProbeHeap(state->resource);
}
