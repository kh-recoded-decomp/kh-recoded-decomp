#include "nitro/types.h"
#pragma opt_common_subs off

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    void *buffer;
    u8 pad_04[8];
} GlyphBuffer;

typedef struct {
    int handle;
    int visibleRows;
    int totalRows;
    u8 pad_0c[0x20];
    int scrollRow;
    int cursorRow;
    u8 pad_34[0x18];
} ScrollList;

typedef struct {
    int textIds[0x3e8 / 4];
    u8 pad_3e8[0x414 - 0x3e8];
} EntryLayout;

typedef struct {
    int selectedEntry;
    u8 pad_0004[0x2c];
    TextLayer layers[4];
    u8 pad_0100[0x180 - 0x100];
    ScrollList lists[2];
    u8 pad_0218[0xcde4 - 0x218];
    GlyphBuffer glyphBuffers[3];
    EntryLayout layouts[1];
    u8 pad_d21c[0xf0cc - 0xd21c];
    int entryCount;
} MenuScene;

extern void *func_ov027_020ba2a8(GlyphBuffer *view, int index);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawShadowedAnchoredText_020bfd68(TextLayer *layer, int x, int y, int color, u32 anchor, void *text);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern int func_020019f4(TextLayer *layer);
extern BOOL IsEntryFlagSet_020c1474(int flagSet, int entryIndex);

void RefreshListPanels_020bfb38(int listIndex, MenuScene *scene)
{
    int detailHeight;
    int entryIndex;
    int y;
    int row;
    EntryLayout *layout;
    int i;
    void *text;
    int count;
    GlyphBuffer *labels;
    GlyphBuffer *names;
    int lineHeight;

    labels = &scene->glyphBuffers[0];
    names = &scene->glyphBuffers[1];
    if ((u32)(listIndex + 1) <= 1) {
        text = func_ov027_020ba2a8(labels, 0);
        CallVirtualHandlerSlot1_02001574(&scene->layers[0], 0);
        DrawShadowedAnchoredText_020bfd68(&scene->layers[0], 4, 2, 3, 0, text);
        Text_UploadTileBuffer_02001520(&scene->layers[0]);
        lineHeight = func_020019f4(&scene->layers[1]);
        CallVirtualHandlerSlot1_02001574(&scene->layers[1], 0);
        for (i = 0; i < scene->entryCount; i++) {
            y = i * (lineHeight + 6);
            row = scene->lists[0].scrollRow;
            if (IsEntryFlagSet_020c1474(0, i + row)) {
                text = func_ov027_020ba2a8(names, i + row);
            } else {
                text = func_ov027_020ba2a8(labels, 2);
            }
            DrawShadowedAnchoredText_020bfd68(&scene->layers[1], 4, y + 4, 1, 0, text);
        }
        Text_UploadTileBuffer_02001520(&scene->layers[1]);
    }
    if (listIndex != 1 && listIndex != -1) {
        return;
    }
    entryIndex = scene->selectedEntry;
    if (IsEntryFlagSet_020c1474(0, entryIndex)) {
        text = func_ov027_020ba2a8(names, entryIndex);
    } else {
        text = func_ov027_020ba2a8(labels, 2);
    }
    CallVirtualHandlerSlot1_02001574(&scene->layers[2], 0);
    DrawShadowedAnchoredText_020bfd68(&scene->layers[2], 4, 4, 3, 0, text);
    Text_UploadTileBuffer_02001520(&scene->layers[2]);
    CallVirtualHandlerSlot1_02001574(&scene->layers[3], 0);
    if (IsEntryFlagSet_020c1474(0, entryIndex)) {
        layout = &scene->layouts[entryIndex];
        detailHeight = func_020019f4(&scene->layers[3]);
        count = scene->lists[1].visibleRows;
        if (scene->lists[1].totalRows < count) {
            count = scene->lists[1].totalRows;
        }
        for (i = 0; i < count; i++) {
            DrawShadowedAnchoredText_020bfd68(&scene->layers[3], 4, i * (detailHeight + 6) + 4, 1, 0,
                                              (void *)layout->textIds[i + scene->lists[1].scrollRow]);
        }
    }
    Text_UploadTileBuffer_02001520(&scene->layers[3]);
}
