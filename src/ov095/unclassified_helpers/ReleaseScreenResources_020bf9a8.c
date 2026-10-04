#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ObjectList;

typedef struct {
    void *ptr;
    u8 rest[8];
} OwnedBuffer;

typedef struct {
    u8 pad0[0x14];
    u8 resource[0xc];
    ObjectList lists[4];
    u8 pad1[0x110e8 - 0x20 - 4 * 0x34];
    OwnedBuffer buffers[2];
} ScreenWork;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void FreePointerIfSet_020ba294(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(void *resource);

void ReleaseScreenResources_020bf9a8(ScreenWork *work) {
    int i;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1_02001574(&work->lists[i], 0);
        FlushBufferAndRunCallback_0200153c(&work->lists[i]);
        DestroyFndObjectList_020014f0(&work->lists[i]);
    }
    for (i = 0; i < 2; i++) {
        FreePointerIfSet_020ba294(&work->buffers[i]);
    }
    FreeResourceBufferAndProbeHeap_02001474(work->resource);
}