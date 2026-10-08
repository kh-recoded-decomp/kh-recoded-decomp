#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct RecordPoint {
    s32 x;
    s32 y;
} RecordPoint;

typedef struct RecordEntry {
    s32 recordIndex;
    RecordPoint position;
    u32 flags;
} RecordEntry;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 unk_08;
    u16 palette;
    u16 unk_0c;
    u16 rowGap;
} TextFrame;

typedef struct TextCursor {
    const u16 *text;
    s32 x;
    s32 y;
    s32 column;
    s32 row;
    s32 textX;
    s32 textY;
} TextCursor;

typedef struct BannerCursor {
    TextCursor text;
    s32 speaker;
    u8 pad_20[0x14];
    s32 blendStart;
} BannerCursor;

typedef struct DialogCursor {
    TextCursor text;
    u8 pad_1c[0x4];
    s32 portraitId;
    s32 speaker;
    u8 pad_28[0x14];
    s32 blendStart;
} DialogCursor;

typedef struct ChoiceCursor {
    s32 scroll;
    u8 pad_04[0x4];
    s32 visibleRows;
    s32 selection;
} ChoiceCursor;

typedef struct TextWindow {
    s32 type;
    s32 style;
    s32 duration;
    s32 unk_0c;
    s32 elapsed;
    s32 x;
    s32 y;
    u8 pad_1c[0x20];
    u8 textLayer[0x34];
    const u16 *message;
    TextFrame frame;
    const u16 *lines[10];
    s32 lineIndex;
    s32 lineCount;
    RecordEntry entries[5];
    u8 pad_104[0x8];
    void *cursor;
} TextWindow;

typedef struct SpeakerAnchor {
    s32 column;
    s32 row;
    s32 flipX;
    s32 flipY;
} SpeakerAnchor;

typedef struct SceneResources {
    u8 pad_00[0x18];
    u8 slots[0x6434];
    NNSG2dFont font;
} SceneResources;

extern SceneResources *data_ov036_020c3844;
extern const SpeakerAnchor data_ov036_020c3588[];
extern const int data_ov036_020c346c[];
extern const RecordPoint data_ov036_020c389c[];
extern const s32 data_ov036_020c34ac[][4];
extern const s32 data_ov036_020c33e4[][2];
extern const s32 data_ov036_020c33b8[];
extern const s32 data_ov036_020c33b0[];

extern int func_020019f4(void *layer);
extern NNSG2dTextRect G2D_MeasureTextRectangle_02016c18(const NNSG2dFont *font, int hSpace, int vSpace, const void *text);
extern void SetSlotEntryFlags_0204f1ac(void *table, int index, u32 flags);
extern void DrawTextWindow_020bebcc(TextWindow *window);
extern void SetRecordEntryEnabled_020bf4fc(RecordEntry *entry, int enabled);
extern void InitRecordEntryAt_020bf530(RecordEntry *entry, int resource, RecordPoint *position, RecordPoint *offset);
extern void SetTimerDuration_020c27dc(TextWindow *window, int duration);

#define ROUND_FX(v) ((int)((v) > 0 ? 0.5f + (float)((v) * 0x1000) : (float)((v) * 0x1000) - 0.5f))

static inline NNSG2dTextRect GetFontTextRect(const NNSG2dFont *font, int hSpace, int vSpace, const u16 *text)
{
    return G2D_MeasureTextRectangle_02016c18(font, hSpace, vSpace, text);
}

static inline NNSG2dTextRect MeasureWithFont(const NNSG2dFont *font, const u16 *text)
{
    return GetFontTextRect(font, 0, 2, text);
}

static inline void PlaceCursorText(TextWindow *window, TextCursor *cursor, NNSG2dTextRect *rect)
{
    int textX;
    int textY;

    if (rect->width >= 0x100) {
        rect->width = 0x100;
    }
    textX = (window->frame.width * 8) / 2 - rect->width / 2;
    cursor->textX = textX;
    textY = (window->frame.height * 8) / 2 - rect->height / 2 - 1;
    cursor->textY = textY;
    cursor->x = textX;
    cursor->y = textY;
    cursor->column = 0;
    cursor->row = 0;
}

void LayoutTextWindow_020c03e0(TextWindow *window)
{
    RecordPoint pos;
    RecordPoint offset;
    int row = 0;

    offset.x = ROUND_FX(window->x);
    offset.y = ROUND_FX(window->y);
    if (window->message != NULL) {
        DrawTextWindow_020bebcc(window);
    }
    switch (window->type) {
    case 4: {
        const NNSG2dFont *font = &data_ov036_020c3844->font;
        BannerCursor *cursor = window->cursor;
        const u16 *text = window->lines[window->lineIndex];
        NNSG2dTextRect rect;
        RecordPoint bannerPos;
        RecordPoint bannerOffset;
        const SpeakerAnchor *anchor;
        int lineHeight;
        int edge;
        int bottom;
        int top;
        int gap;
        int slot;
        int enabled;
        u32 flags;

        if (window->message != NULL) {
            rect = MeasureWithFont(font, text);
            PlaceCursorText(window, &cursor->text, &rect);
        }
        bannerOffset.x = ROUND_FX(window->x);
        bannerOffset.y = ROUND_FX(window->y);
        lineHeight = func_020019f4(window->textLayer);
        edge = window->frame.x + window->frame.width;
        bottom = window->frame.y + window->frame.height;
        slot = 4;
        if (window->style == 15) {
            slot = 8;
        }
        bannerPos.x = ROUND_FX(edge * 8);
        bannerPos.y = ROUND_FX(bottom * 8 + lineHeight / 2 - slot);
        InitRecordEntryAt_020bf530(&window->entries[0], 0, &bannerPos, &bannerOffset);
        slot = cursor->speaker;
        anchor = &data_ov036_020c3588[slot];
        top = window->frame.y * 8;
        bottom = window->frame.height * 8 + top;
        gap = 4;
        enabled = 1;
        if (slot == 16) {
            enabled = 0;
        }
        if (window->style == 15) {
            gap = 0;
        }
        if (slot <= 7) {
            pos.y = ROUND_FX(top - gap);
        } else {
            pos.y = ROUND_FX(bottom + gap);
        }
        edge = anchor->column * ((window->frame.width * 8) / 3);
        pos.x = ROUND_FX(edge + window->frame.x * 8);
        InitRecordEntryAt_020bf530(&window->entries[4], data_ov036_020c346c[window->style], &pos, &offset);
        SetRecordEntryEnabled_020bf4fc(&window->entries[4], enabled);
        flags = 0;
        if (anchor->flipX) {
            flags |= 1;
        }
        if (anchor->flipY) {
            flags |= 2;
        }
        SetSlotEntryFlags_0204f1ac(data_ov036_020c3844->slots, window->entries[4].recordIndex, flags);
        if (cursor->blendStart > 0) {
            SetTimerDuration_020c27dc(window, 11);
            return;
        }
        SetTimerDuration_020c27dc(window, 6);
        return;
    }
    case 0: {
        const NNSG2dFont *font = &data_ov036_020c3844->font;
        DialogCursor *cursor = window->cursor;
        const u16 *text = window->lines[window->lineIndex];
        NNSG2dTextRect rect;
        RecordPoint dialogPos;
        RecordPoint dialogOffset;
        const SpeakerAnchor *anchor;
        int speaker;
        int enabled;
        u32 flags;

        if (window->message != NULL) {
            rect = MeasureWithFont(font, text);
            PlaceCursorText(window, &cursor->text, &rect);
        }
        dialogOffset.x = ROUND_FX(window->x);
        dialogOffset.y = ROUND_FX(window->y);
        if (window->style >= 7) {
            dialogPos.x = 0x90000;
            dialogPos.y = 0x68000;
        } else {
            dialogPos = data_ov036_020c389c[cursor->portraitId];
        }
        InitRecordEntryAt_020bf530(&window->entries[0], 0, &dialogPos, &dialogOffset);
        speaker = cursor->speaker;
        anchor = &data_ov036_020c3588[speaker];
        enabled = 1;
        if (speaker == 16) {
            enabled = 0;
        }
        if (window->style <= 7) {
            dialogPos.x = data_ov036_020c34ac[cursor->portraitId][anchor->column];
            dialogPos.y = data_ov036_020c33e4[cursor->portraitId][anchor->row];
        } else {
            dialogPos.x = data_ov036_020c33b8[anchor->column];
            dialogPos.y = data_ov036_020c33b0[anchor->row];
        }
        InitRecordEntryAt_020bf530(&window->entries[4], data_ov036_020c346c[window->style], &dialogPos, &dialogOffset);
        SetRecordEntryEnabled_020bf4fc(&window->entries[4], enabled);
        flags = 0;
        if (anchor->flipX) {
            flags |= 1;
        }
        if (anchor->flipY) {
            flags |= 2;
        }
        SetSlotEntryFlags_0204f1ac(data_ov036_020c3844->slots, window->entries[4].recordIndex, flags);
        if (cursor->blendStart > 0) {
            SetTimerDuration_020c27dc(window, 11);
            return;
        }
        SetTimerDuration_020c27dc(window, 6);
        return;
    }
    case 1: {
        ChoiceCursor *cursor = window->cursor;
        int lineHeight = func_020019f4(window->textLayer);
        int last = cursor->visibleRows - 1;
        int selection = cursor->selection;
        int gap = window->frame.rowGap;

        if (selection > last) {
            cursor->scroll = selection - last;
            row = cursor->visibleRows - 1;
        } else {
            cursor->scroll = 0;
            row = cursor->selection;
        }
        pos.x = ROUND_FX(window->frame.x * 8 + 4);
        pos.y = ROUND_FX(window->frame.y * 8 + lineHeight / 2 + 1 + row * (lineHeight + gap));
        InitRecordEntryAt_020bf530(&window->entries[1], 1, &pos, &offset);
        SetRecordEntryEnabled_020bf4fc(&window->entries[1], 1);
        pos.x = 0x80000;
        pos.y = ROUND_FX((window->frame.y - 1) * 8);
        InitRecordEntryAt_020bf530(&window->entries[2], 2, &pos, &offset);
        pos.y = ROUND_FX((window->frame.y + 1 + window->frame.height) * 8);
        InitRecordEntryAt_020bf530(&window->entries[3], 3, &pos, &offset);
        SetTimerDuration_020c27dc(window, 12);
        return;
    }
    case 2:
    case 3: {
        int lineHeight = func_020019f4(window->textLayer);
        int right = window->frame.x + window->frame.width;
        int bottom = window->frame.y + window->frame.height;

        pos.x = ROUND_FX(right * 8);
        pos.y = ROUND_FX(bottom * 8 + lineHeight / 2 - 4);
        InitRecordEntryAt_020bf530(&window->entries[0], 0, &pos, &offset);
        SetRecordEntryEnabled_020bf4fc(&window->entries[0], 1);
        SetTimerDuration_020c27dc(window, 8);
        return;
    }
    }
}
