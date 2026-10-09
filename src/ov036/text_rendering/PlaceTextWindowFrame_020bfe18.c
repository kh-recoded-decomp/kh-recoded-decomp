#include "nitro/types.h"

typedef struct TextSize {
    s32 width;
    s32 height;
} TextSize;

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 unk_0c;
    u16 rowGap;
} TextFrame;

typedef struct FrameRect {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} FrameRect;

typedef struct RecordEntry {
    s32 recordIndex;
    s32 x;
    s32 y;
    u32 flags;
} RecordEntry;

typedef struct DialogCursor {
    u8 pad_00[0x20];
    s32 portraitId;
} DialogCursor;

typedef struct ChoiceCursor {
    s32 scroll;
    s32 unk_04;
    s32 visibleRows;
    s32 selection;
    s32 lineCount;
} ChoiceCursor;

typedef struct TextWindow {
    s32 type;
    s32 style;
    s32 duration;
    s32 unk_0c;
    s32 elapsed;
    s32 x;
    s32 y;
    u8 pad_1c[0x10];
    s32 textScreen;
    u8 pad_30[0xc];
    u8 textLayer[0x34];
    const u16 *message;
    TextFrame frame;
    const u16 *lines[10];
    s32 lineIndex;
    s32 lineCount;
    RecordEntry entries[5];
    s32 halfWidth;
    s32 halfHeight;
    void *cursor;
} TextWindow;

typedef struct SceneResources {
    u8 pad_00[0x644c];
    u8 font[0x1c0];
    TextWindow windows[2];
    s32 windowCount;
} SceneResources;

extern SceneResources *data_ov036_020c3844;
extern const FrameRect data_ov036_020c340c[];

extern void MeasureTextWindowTiles_020bf2f4(TextSize *outTiles, int compact, const u16 *text, int padX, int padY);
extern BOOL InitTextLayerAt_020014b0(void *layer, int screen, u16 *screenBase, void *font, TextFrame *frame);
extern int func_020019f4(void *layer);
extern BOOL DestroyFndObjectList_020014f0(void *layer);
extern void SetTimerDuration_020c27dc(TextWindow *window, int duration);

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define REG_BG2OFS_ADDR 0x04000018
#define REG_BG3OFS_ADDR 0x0400001c

static inline void SetBgOffsetAt(u32 addr, int hOffset, int vOffset)
{
    *(u32 *)addr = (u32)((hOffset & 0x1ff) | ((vOffset << 16) & 0x1ff0000));
}

static inline void SetBgOffset(int screen, int hOffset, int vOffset)
{
    if (screen == 2) {
        SetBgOffsetAt(REG_BG2OFS_ADDR, hOffset, vOffset);
    } else {
        SetBgOffsetAt(REG_BG3OFS_ADDR, hOffset, vOffset);
    }
}

static inline void ScrollWindowBg(TextWindow *window)
{
    int hOffset = -window->x;
    int vOffset = -window->y;

    SetBgOffset(window->textScreen, hOffset, vOffset);
}

void PlaceTextWindowFrame_020bfe18(TextWindow *window)
{
    TextFrame *frame = &window->frame;
    int i;
    int halfHeight;
    int halfWidth;
    int marginX;
    int marginY;

    window->frame.x = 9;
    frame->y = 0xc;
    frame->width = 0xe;
    frame->height = 9;
    frame->charBase = 0xc0;
    frame->palette = 0xf;
    frame->unk_0c = 0;
    frame->rowGap = 2;
    if (window->textScreen == 3) {
        frame->charBase += 0x80;
    }
    window->elapsed = 0;
    for (i = 0; i < 5; i++) {
        window->entries[i].recordIndex = -1;
    }
    switch (window->type) {
    case 0: {
        DialogCursor *cursor = window->cursor;
        int portrait = cursor->portraitId;
        if (portrait >= 0) {
            frame->x = data_ov036_020c340c[portrait].x;
            frame->y = data_ov036_020c340c[portrait].y;
            frame->width = data_ov036_020c340c[portrait].width;
            frame->height = data_ov036_020c340c[portrait].height;
        }
        break;
    }
    case 1: {
        ChoiceCursor *cursor;
        TextSize size;
        int lineHeight;
        int space;
        const u16 *text;

        frame->rowGap = 8;
        cursor = window->cursor;
        MeasureTextWindowTiles_020bf2f4(&size, window->type, window->message, 0x18, 4);
        if (size.height == 9) {
            size.width = 0xe;
        }
        frame->width = size.width;
        frame->height = size.height;
        frame->x = 0x10 - ((u32)frame->width >> 1);
        frame->y = 0xc - ((u32)frame->height >> 1);
        InitTextLayerAt_020014b0(window->textLayer, window->textScreen, NULL, data_ov036_020c3844->font, frame);
        lineHeight = func_020019f4(window->textLayer);
        DestroyFndObjectList_020014f0(window->textLayer);
        cursor->unk_04 = 0;
        cursor->scroll = 0;
        cursor->visibleRows = 0;
        space = frame->height * 8;
        while (space > lineHeight) {
            cursor->visibleRows++;
            space = space - lineHeight - window->frame.rowGap;
        }
        text = window->message;
        cursor->lineCount = 0;
        while (*text != 0) {
            if (*text == 10) {
                cursor->lineCount++;
            }
            text++;
        }
        cursor->lineCount++;
        if (cursor->selection > cursor->lineCount - 1) {
            cursor->selection = cursor->lineCount - 1;
        }
        break;
    }
    case 2:
    case 3: {
        TextSize size;

        frame->x = 10;
        frame->y = 9;
        frame->width = 0xc;
        frame->height = 7;
        MeasureTextWindowTiles_020bf2f4(&size, window->type, window->message, 0, 0);
        frame->width = size.width;
        frame->height = size.height;
        frame->x = 0x10 - ((u32)frame->width >> 1);
        frame->y = 0xc - ((u32)frame->height >> 1);
        break;
    }
    case 4: {
        int maxWidth = 0;
        int maxHeight = 0;
        TextSize size;
        TextSize rect;

        frame->x = 0;
        frame->y = 0;
        frame->width = 0x14;
        frame->height = 10;
        for (i = 0; i < window->lineCount; i++) {
            MeasureTextWindowTiles_020bf2f4(&rect, window->type, window->lines[i], 0, 0);
            size = rect;
            if (maxWidth < size.width) {
                maxWidth = size.width;
            }
            if (maxHeight < size.height) {
                maxHeight = size.height;
            }
        }
        frame->width = maxWidth;
        frame->height = maxHeight;
        frame->x = 0x10 - ((u32)frame->width >> 1);
        frame->y = 0xc - ((u32)frame->height >> 1);
        break;
    }
    }
    marginX = 0xc;
    marginY = 0xc;
    if (window->type == 1) {
        marginY = 0x14;
    }
    if (window->style == 0xf) {
        marginX = 0x14;
    }
    halfWidth = marginX + ((u32)frame->width >> 1) * 8;
    halfHeight = marginY + ((u32)frame->height >> 1) * 8;
    window->halfWidth = halfWidth;
    window->halfHeight = halfHeight;
    switch (window->type) {
    case 4: {
        int centerX = window->x + 0x80;
        int centerY = window->y + 0x60;
        int left = centerX - halfWidth;
        int right = centerX + halfWidth;
        int top = centerY - halfHeight;
        int bottom = centerY + halfHeight;

        if (left < 0) {
            centerX -= left;
        } else if (right > 0x100) {
            centerX += 0x100 - right;
        }
        if (top < 0) {
            centerY -= top;
        } else if (bottom > 0xc0) {
            centerY += 0xc0 - bottom;
        }
        window->x = centerX - 0x80;
        window->y = centerY - 0x60;
        ScrollWindowBg(window);
        break;
    }
    case 1: {
        SceneResources *scene = data_ov036_020c3844;
        TextWindow *other = &scene->windows[0];
        int dx;
        int dy;
        int overlap;

        if (scene->windowCount <= 1 || other->type != 4) {
            break;
        }
        dx = window->x - other->x;
        dy = window->y - other->y;
        halfWidth += other->halfWidth;
        halfHeight += other->halfHeight;
        if (dx < 0) {
            dx = -dx;
        }
        if (dx >= halfWidth || ABS(dy) >= halfHeight) {
            break;
        }
        overlap = halfHeight - ABS(dy);
        if (dy < 0) {
            window->y -= overlap;
        } else if (dy > 0) {
            window->y += overlap;
        }
        ScrollWindowBg(window);
        break;
    }
    }
    SetTimerDuration_020c27dc(window, 4);
}
