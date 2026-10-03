#include "nitro/types.h"

typedef struct TextSize {
    s32 width;
    s32 height;
} TextSize;

typedef struct ImageHeader {
    u8 pad_00[0x8];
    u32 size;
} ImageHeader;

typedef struct TextCursor {
    u8 pad_00[0x20];
    int sizeClass;
} TextCursor;

typedef struct TextWindow {
    int kind;
    int style;
    u8 pad_08[0xc];
    int scrollX;
    int scrollY;
    u8 pad_1c[0x8];
    int screen;
    u8 pad_28[0x8];
    u32 imageId;
    void *imageBuffer;
    ImageHeader *graphics;
    u8 pad_3c[0x48];
    u16 *lines[10];
    int lineIndex;
    int lineCount;
    u8 pad_0b4[0x58];
    TextCursor *cursor;
} TextWindow;

typedef struct PaletteSource {
    u8 pad_00[0x8];
    u32 size;
    u8 *data;
} PaletteSource;

typedef struct HandlerOwner {
    u8 pad_00[0x10];
    u32 count;
} HandlerOwner;

typedef struct OverlayWork {
    u8 pad_00[0x4];
    u32 imageBase;
    u8 pad_08[0x8];
    HandlerOwner *frameGraphics;
    PaletteSource *palette;
} OverlayWork;

extern OverlayWork *data_ov036_020c3844;
extern u32 data_ov036_020c33c8[];
extern u32 data_ov036_020c34fc[][5];
extern void MeasureTextWindowTiles_020bf2f4(TextSize *outTiles, int compact, const u16 *text, int padX, int padY);
extern void SetDisplayLayersVisible_020c2768(TextWindow *window, BOOL enable);
extern void *AllocAndRegisterOrFree_0202b504(ImageHeader **graphics, u32 key, int kind);
extern void func_02007250(const void *src, u32 offset, u32 size);
extern void func_ov036_020bf670(int screen, HandlerOwner *owner, u32 arg0, u32 arg1);
extern void func_ov036_020bf698(int screen, ImageHeader *graphics, u32 arg0, u32 arg1);
extern void SetTimerDuration_020c27dc(TextWindow *window, int duration);

#define REG_BG2CNT (*(vu16 *)0x0400000c)
#define REG_BG3CNT (*(vu16 *)0x0400000e)
#define REG_BG2OFS (*(vu32 *)0x04000018)
#define REG_BG3OFS (*(vu32 *)0x0400001c)

void LoadTextWindowFrame_020bfb0c(TextWindow *window)
{
    TextCursor *cursor;
    TextSize size;
    TextSize rect;
    int maxWidth;
    int maxHeight;
    int i;
    int x;
    int y;
    u32 paletteSize;

    switch (window->kind) {
    case 4:
        switch (window->style) {
        case 14:
            window->imageId = 0x1a;
            break;
        case 15:
            window->imageId = 2;
            break;
        default:
            window->imageId = 1;
            break;
        }
        break;
    case 2:
    case 3:
        window->imageId = 0x19;
        break;
    case 1:
        window->imageId = 1;
        break;
    case 0:
        cursor = window->cursor;
        switch (window->style) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            window->imageId = data_ov036_020c33c8[window->style - 7];
            cursor->sizeClass = 3;
            break;
        default:
            if (window->style >= 3 && window->style <= 6) {
                cursor->sizeClass = 3;
            } else {
                maxWidth = 0;
                maxHeight = 0;
                for (i = 0; i < window->lineCount; i++) {
                    MeasureTextWindowTiles_020bf2f4(&rect, window->kind, window->lines[i], 0, 0);
                    size = rect;
                    if (maxWidth < size.width) {
                        maxWidth = size.width;
                    }
                    if (maxHeight < size.height) {
                        maxHeight = size.height;
                    }
                }
                if (maxHeight <= 2) {
                    cursor->sizeClass = 0;
                } else if (maxHeight > 4) {
                    cursor->sizeClass = 4;
                } else if (maxWidth < 8) {
                    cursor->sizeClass = 1;
                } else if (maxWidth < 12) {
                    cursor->sizeClass = 2;
                } else {
                    cursor->sizeClass = 3;
                }
            }
            window->imageId = data_ov036_020c34fc[window->style][cursor->sizeClass];
            break;
        }
        break;
    }
    SetDisplayLayersVisible_020c2768(window, FALSE);
    window->imageBuffer = AllocAndRegisterOrFree_0202b504(&window->graphics, (((data_ov036_020c3844->imageBase + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (window->imageId & 0x1ff), 0xe);
    paletteSize = data_ov036_020c3844->palette->size;
    func_02007250(data_ov036_020c3844->palette->data + 0x1c0, paletteSize - paletteSize / 8, paletteSize / 8);
    func_ov036_020bf670(window->screen, data_ov036_020c3844->frameGraphics, 0, data_ov036_020c3844->frameGraphics->count);
    func_ov036_020bf698(window->screen, window->graphics, 0, window->graphics->size);
    x = -window->scrollX;
    y = -window->scrollY;
    if (window->screen == 2) {
        REG_BG2CNT = (u16)(REG_BG2CNT & ~3);
        REG_BG3CNT = (u16)((REG_BG3CNT & ~3) | 1);
        REG_BG2OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
    } else {
        REG_BG3CNT = (u16)(REG_BG3CNT & ~3);
        REG_BG2CNT = (u16)((REG_BG2CNT & ~3) | 1);
        REG_BG3OFS = (x & 0x1ff) | ((y << 16) & 0x1ff0000);
    }
    SetTimerDuration_020c27dc(window, 3);
}
