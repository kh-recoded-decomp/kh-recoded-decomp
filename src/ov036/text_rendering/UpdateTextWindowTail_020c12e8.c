#include "nitro/types.h"

#define REG_BG2OFS (*(vu32 *)0x04000018)
#define REG_BG3OFS (*(vu32 *)0x0400001c)

typedef struct RecordPoint {
    s32 x;
    s32 y;
} RecordPoint;

typedef struct TailSwing {
    s32 angle;
    s32 velocity;
    s32 phase;
    s32 offsetX;
    s32 offsetY;
    s32 divisor;
    s32 decay;
} TailSwing;

typedef struct DialogCursor {
    u8 pad_00[0x20];
    s32 portraitId;
    s32 speaker;
    TailSwing swing;
} DialogCursor;

typedef struct BannerCursor {
    u8 pad_00[0x1c];
    s32 speaker;
    TailSwing swing;
} BannerCursor;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} TextFrame;

typedef struct TextWindow {
    s32 type;
    s32 style;
    u8 pad_08[0xc];
    s32 x;
    s32 y;
    u8 pad_1c[0x10];
    s32 bgLayer;
    u8 pad_30[0x44];
    TextFrame frame;
    u8 pad_7c[0x78];
    s32 tailRecord;
    u8 pad_f8[0x14];
    void *cursor;
} TextWindow;

typedef struct SpeakerAnchor {
    s32 column;
    s32 row;
    s32 flipX;
    s32 flipY;
} SpeakerAnchor;

extern u8 *data_ov036_020c3844;
extern const SpeakerAnchor data_ov036_020c3588[];
extern const s32 data_ov036_020c34ac[][4];
extern const s32 data_ov036_020c33e4[][2];
extern const s32 data_ov036_020c33b8[];
extern const s32 data_ov036_020c33b0[];

extern void func_0204f13c(void *table, int index, RecordPoint *position);
extern void SetTimerDuration_020c27dc(TextWindow *window, int duration);

#define ROUND_FX(v) ((int)((v) > 0 ? 0.5f + (float)((v) * 0x1000) : (float)((v) * 0x1000) - 0.5f))

void UpdateTextWindowTail_020c12e8(TextWindow *window)
{
    RecordPoint dialogPos;
    RecordPoint bannerPos;

    switch (window->type) {
    case 0: {
        DialogCursor *cursor = window->cursor;
        TailSwing *swing = &cursor->swing;
        const SpeakerAnchor *anchor;
        int delta;
        int offsetX;
        int offsetY;

        if (swing->phase != 0) {
            delta = swing->velocity - swing->angle;
        } else {
            delta = -(swing->velocity + swing->angle);
        }
        swing->angle += (int)(((s64)delta * 0x800 + 0x800) >> 12);
        swing->phase = swing->phase == 0;
        swing->velocity -= swing->decay / swing->divisor;
        swing->offsetX = swing->angle;
        swing->offsetY = swing->angle >> 1;
        if (swing->velocity < 0x29) {
            swing->offsetX = 0;
            swing->offsetY = 0;
            SetTimerDuration_020c27dc(window, 6);
        }
        offsetX = swing->offsetX >> 12;
        offsetX += -window->x;
        offsetY = swing->offsetY >> 12;
        offsetY += -window->y;
        if (window->bgLayer == 2) {
            REG_BG2OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
        } else {
            REG_BG3OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
        }
        anchor = &data_ov036_020c3588[cursor->speaker];
        if (window->style <= 7) {
            dialogPos.x = data_ov036_020c34ac[cursor->portraitId][anchor->column];
            dialogPos.y = data_ov036_020c33e4[cursor->portraitId][anchor->row];
        } else {
            dialogPos.x = data_ov036_020c33b8[anchor->column];
            dialogPos.y = data_ov036_020c33b0[anchor->row];
        }
        dialogPos.x += ROUND_FX(window->x);
        dialogPos.y += ROUND_FX(window->y);
        dialogPos.x += swing->offsetX;
        dialogPos.y += swing->offsetY;
        func_0204f13c(data_ov036_020c3844 + 0x18, window->tailRecord, &dialogPos);
        return;
    }
    case 1:
        return;
    case 4: {
        BannerCursor *cursor = window->cursor;
        TailSwing *swing = &cursor->swing;
        const SpeakerAnchor *anchor;
        int delta;
        int offsetX;
        int offsetY;
        int edge;
        int gap;
        int top;
        int bottom;
        int speaker;

        if (swing->phase != 0) {
            delta = swing->velocity - swing->angle;
        } else {
            delta = -(swing->velocity + swing->angle);
        }
        swing->angle += (int)(((s64)delta * 0x800 + 0x800) >> 12);
        swing->phase = swing->phase == 0;
        swing->velocity -= swing->decay / swing->divisor;
        swing->offsetX = swing->angle;
        swing->offsetY = swing->angle >> 1;
        if (swing->velocity < 0x29) {
            swing->offsetX = 0;
            swing->offsetY = 0;
            SetTimerDuration_020c27dc(window, 6);
        }
        offsetX = swing->offsetX >> 12;
        offsetX += -window->x;
        offsetY = swing->offsetY >> 12;
        offsetY += -window->y;
        if (window->bgLayer == 2) {
            REG_BG2OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
        } else {
            REG_BG3OFS = (u32)((offsetX & 0x1ff) | ((offsetY << 16) & 0x01ff0000));
        }
        speaker = cursor->speaker;
        anchor = &data_ov036_020c3588[speaker];
        top = window->frame.y * 8;
        bottom = window->frame.height * 8 + top;
        gap = 4;
        if (window->style == 15) {
            gap = 0;
        }
        if (speaker <= 7) {
            bannerPos.y = ROUND_FX(top - gap);
        } else {
            bannerPos.y = ROUND_FX(bottom + gap);
        }
        edge = anchor->column * ((window->frame.width * 8) / 3);
        bannerPos.x = ROUND_FX(edge + window->frame.x * 8);
        bannerPos.x += ROUND_FX(window->x);
        bannerPos.y += ROUND_FX(window->y);
        bannerPos.x += swing->offsetX;
        bannerPos.y += swing->offsetY;
        func_0204f13c(data_ov036_020c3844 + 0x18, window->tailRecord, &bannerPos);
        return;
    }
    }
}
