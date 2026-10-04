#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} ResourceLoader;

typedef struct {
    void *buffer;
    u8 pad_04[8];
} OwnedBuffer;

typedef struct {
    u8 pad_0000[0xc];
    u8 resourceBuffer[0xc];
    ResourceLoader loaders[6];
    u8 pad_0150[0xcf1c - 0x150];
    OwnedBuffer buffers[4];
} SceneWork;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern void DestroyFndObjectList_020014f0(void *context);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void FreeResourceBufferAndProbeHeap_02001474(void *buffer);

void ReleaseSceneResources_020bfcf0(SceneWork *work)
{
    int i;

    for (i = 0; i < 6; i++) {
        CallVirtualHandlerSlot1_02001574(&work->loaders[i], 0);
        FlushBufferAndRunCallback_0200153c(&work->loaders[i]);
        DestroyFndObjectList_020014f0(&work->loaders[i]);
    }
    for (i = 0; i < 4; i++) {
        FreePointerIfSet_020ba294(&work->buffers[i].buffer);
    }
    FreeResourceBufferAndProbeHeap_02001474(work->resourceBuffer);
}
