#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 pad_00[0x10];
    u8 font[0xc];
    TextLayer textLayers[2];
    u8 pad_84[0xc9e8 - 0x84];
    void *unk_C9E8;
} MenuScene;

extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int color);
extern void FlushBufferAndRunCallback_0200153c(TextLayer *layer);
extern void DestroyFndObjectList_020014f0(TextLayer *layer);
extern void FreePointerIfSet_020ba294(void **pointer);
extern void ReleaseFont_02001474(void *font);

void ReleaseTextLayers_020bf4e4(MenuScene *scene)
{
    int i;

    for (i = 0; i < 2; i++) {
        CallVirtualHandlerSlot1_02001574(&scene->textLayers[i], 0);
        FlushBufferAndRunCallback_0200153c(&scene->textLayers[i]);
        DestroyFndObjectList_020014f0(&scene->textLayers[i]);
    }
    FreePointerIfSet_020ba294(&scene->unk_C9E8);
    ReleaseFont_02001474(scene->font);
}
