#include "nitro/types.h"

typedef struct TextLayer {
    u8 reserved[0x34];
} TextLayer;

typedef struct PackedTextView {
    u32 header;
    u32 count;
    u8 *records;
} PackedTextView;

typedef struct ScrollPanel {
    u8 reserved00[0x2c];
    int scroll;
    int cursor;
} ScrollPanel;

typedef struct TheaterState {
    int selection;
    u8 reserved04[0x20];
    TextLayer layers[4];
    u8 reserved0f4[0xcacc - 0xf4];
    ScrollPanel panel;
    u8 reservedcb00[0xcb64 - 0xcb00];
    PackedTextView views[3];
} TheaterState;

enum { ROW_INDEX, ROW_ADVANCE };

extern const u16 *GetPackedText(PackedTextView *view, int index);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int value);
extern void DrawShadowedAnchoredText(TextLayer *layer, int x, int y, int color,
                                   u32 anchor, const u16 *text);
extern void Text_UploadTileBuffer(TextLayer *layer);
extern u32 GetNestedModeByte(TextLayer *layer);
extern BOOL IsTheaterEntryFlagSet(int flagSet, int index);

void RedrawTheaterReportText_020bf39c(int unused, TheaterState *state)
{
    int counterMetric;
    int selection = state->selection;
    PackedTextView *commonText = &state->views[0];
    TextLayer *titleLayer;
    PackedTextView *entryTitles = &state->views[1];
    int rowOffset;
    int scroll;
    ScrollPanel *panel;
    PackedTextView *descriptions = &state->views[2];
    int entryRow;
    const u16 *text;
    int metrics[2];
    int visibleRow;
    int textY;

    text = GetPackedText(commonText, 0);
    CallVirtualHandlerSlot1(&state->layers[0], 0);
    DrawShadowedAnchoredText(&state->layers[0], 4, 2, 3, 0, text);
    Text_UploadTileBuffer(&state->layers[0]);

    panel = &state->panel;
    metrics[ROW_ADVANCE] = GetNestedModeByte(&state->layers[3]);
    CallVirtualHandlerSlot1(&state->layers[3], 0);
    counterMetric = ROW_INDEX;
    metrics[ROW_ADVANCE] += 6;
    for (metrics[counterMetric] = 0; metrics[counterMetric] < 9; metrics[counterMetric]++) {
        visibleRow = metrics[counterMetric];
        rowOffset = metrics[ROW_INDEX] * metrics[ROW_ADVANCE];
        scroll = panel->scroll;
        textY = rowOffset;
        entryRow = visibleRow;
        if (IsTheaterEntryFlagSet(0, entryRow + scroll)) {
            text = GetPackedText(entryTitles, metrics[ROW_INDEX] + scroll);
        } else {
            text = GetPackedText(commonText, 1);
        }
        DrawShadowedAnchoredText(&state->layers[3], 0, textY + 4, 1, 0, text);
    }
    Text_UploadTileBuffer(&state->layers[3]);

    titleLayer = &state->layers[1];
    if (IsTheaterEntryFlagSet(0, selection)) {
        text = GetPackedText(entryTitles, selection);
    } else {
        text = GetPackedText(commonText, 1);
    }
    CallVirtualHandlerSlot1(titleLayer, 0);
    DrawShadowedAnchoredText(titleLayer, 0x7c, 4, 3, 0x10, text);
    Text_UploadTileBuffer(titleLayer);

    if (IsTheaterEntryFlagSet(0, selection)) {
        text = GetPackedText(descriptions, selection);
    } else {
        text = GetPackedText(commonText, 2);
    }
    CallVirtualHandlerSlot1(&state->layers[2], 0);
    DrawShadowedAnchoredText(&state->layers[2], 0xa0, 0x14, 5, 0x20, text);
    Text_UploadTileBuffer(&state->layers[2]);
}
