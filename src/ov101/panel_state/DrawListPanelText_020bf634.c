#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 data[0xc];
} PackedFileView;

typedef struct {
    s32 listId;
    s32 itemCount;
    s32 visibleRows;
    s32 entryIndex;
    u8 pad_10[0x1C];
    s32 scroll;
    s32 cursor;
    u8 pad_34[0x18];
} ScrollPanel;

typedef struct {
    s32 nameIndex;
    s32 descIndex;
} EntryText;

typedef struct {
    s32 mode;
    u8 pad_0004[0x38];
    TextLayer layers[4];
    u8 pad_010C[0xCD64 - 0x10C];
    ScrollPanel panels[2];
    u8 pad_CDFC[0xCFA0 - 0xCDFC];
    PackedFileView views[3];
} Ov101State;

extern const EntryText data_ov101_020c1058[];
extern void *func_ov027_020ba2a8(PackedFileView *view, int index);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void DrawShadowedAnchoredText_020bf840(TextLayer *layer, int x, int y, int color, u32 anchor, void *text);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern int func_020019f4(TextLayer *layer);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern BOOL IsStateFlagSet_020c07a8(int setIndex, int bitIndex);

void DrawListPanelText_020bf634(int which, Ov101State *state)
{
    PackedFileView *commonView = &state->views[0];
    PackedFileView *nameView = &state->views[2];
    PackedFileView *descView = &state->views[1];
    const EntryText *entry;
    void *text;
    int y;
    ScrollPanel *panel;
    int i;
    int row;
    int mode;
    BOOL known;

    if ((u32)(which + 1) <= 1) {
        i = 0;
        text = func_ov027_020ba2a8(commonView, 0);
        CallVirtualHandlerSlot1_02001574(&state->layers[0], 0);
        DrawShadowedAnchoredText_020bf840(&state->layers[0], 4, 2, 3, 0, text);
        Text_UploadTileBuffer_02001520(&state->layers[0]);
        panel = &state->panels[0];
        CallVirtualHandlerSlot1_02001574(&state->layers[1], 0);
        for (; i < panel->itemCount; i++) {
            y = i * (func_020019f4(&state->layers[1]) + 6);
            row = panel->scroll + i;
            if (row == 7) {
                known = IsGlobalPackedBitSet_02027304(0xa0d);
            } else {
                known = IsStateFlagSet_020c07a8(0, row);
            }
            if (known) {
                text = func_ov027_020ba2a8(nameView, data_ov101_020c1058[row].nameIndex);
            } else {
                text = func_ov027_020ba2a8(commonView, 3);
            }
            DrawShadowedAnchoredText_020bf840(&state->layers[1], 4, y + 4, 1, 0, text);
        }
        Text_UploadTileBuffer_02001520(&state->layers[1]);
    }
    if (which != 1 && which != -1) {
        return;
    }
    text = func_ov027_020ba2a8(commonView, 2);
    CallVirtualHandlerSlot1_02001574(&state->layers[2], 0);
    DrawShadowedAnchoredText_020bf840(&state->layers[2], 4, 4, 3, 0, text);
    Text_UploadTileBuffer_02001520(&state->layers[2]);
    mode = state->mode;
    entry = &data_ov101_020c1058[mode];
    text = func_ov027_020ba2a8(descView, entry->descIndex);
    CallVirtualHandlerSlot1_02001574(&state->layers[3], 0);
    if (mode == 7) {
        known = IsGlobalPackedBitSet_02027304(0xa0d);
    } else {
        known = IsStateFlagSet_020c07a8(0, mode);
    }
    if (known) {
        DrawShadowedAnchoredText_020bf840(&state->layers[3], 4, 4, 1, 0, text);
    }
    Text_UploadTileBuffer_02001520(&state->layers[3]);
}
