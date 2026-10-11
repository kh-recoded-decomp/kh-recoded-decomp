#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct EntryTextLayer {
    u8 pad00[0x14];
    NNSG2dFont *font;
    u8 pad18[4];
    int verticalSpacing;
    u8 pad20[0x14];
} EntryTextLayer;

typedef struct EntryMenuTextState {
    u8 pad000[0x784];
    EntryTextLayer caption;
    EntryTextLayer title;
    EntryTextLayer header;
    EntryTextLayer labels[2];
    EntryTextLayer page;
    EntryTextLayer hint;
    void *messageFile;
} EntryMenuTextState;

typedef char EntryTextLayerMustBe52Bytes[
    sizeof(EntryTextLayer) == 0x34 ? 1 : -1];
typedef char EntryMessagesMustStartAt8f0[
    (u32)&((EntryMenuTextState *)0)->messageFile == 0x8f0 ? 1 : -1];

extern BOOL DestroyFndObjectList(void *container);
extern void FreePointerIfSet(void **pointer);

void ReleaseEntryMenuTextLayers(EntryMenuTextState *menu)
{
    int i;
    DestroyFndObjectList(&menu->page);
    DestroyFndObjectList(&menu->header);
    DestroyFndObjectList(&menu->title);
    DestroyFndObjectList(&menu->caption);
    DestroyFndObjectList(&menu->hint);
    for (i = 0; i < 2; i++) {
        DestroyFndObjectList(&menu->labels[i]);
    }
    FreePointerIfSet(&menu->messageFile);
}
