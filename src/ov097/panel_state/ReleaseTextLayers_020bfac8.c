#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    void *buffer;
    u8 pad_04[8];
} GlyphBuffer;

typedef struct {
    u8 pad_0000[0x24];
    u8 resource[0xc];
    TextLayer layers[4];
    u8 pad_0100[0xcde4 - 0x100];
    GlyphBuffer glyphBuffers[3];
} MenuScene;

extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *context);
extern BOOL DestroyFndObjectList_020014f0(void *container);
extern void FreePointerIfSet_020ba294(void *ptr);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(void *resource);

void ReleaseTextLayers_020bfac8(MenuScene *scene)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        CallVirtualHandlerSlot1_02001574(&scene->layers[i], 0);
        FlushBufferAndRunCallback_0200153c(&scene->layers[i]);
        DestroyFndObjectList_020014f0(&scene->layers[i]);
    }
    for (j = 0; j < 3; j++) {
        FreePointerIfSet_020ba294(&scene->glyphBuffers[j]);
    }
    FreeResourceBufferAndProbeHeap_02001474(scene->resource);
}
