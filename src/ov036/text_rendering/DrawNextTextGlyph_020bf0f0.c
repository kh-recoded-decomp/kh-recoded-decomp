#include "nitro/types.h"

typedef struct TextCursor {
    u16 *text;
    int x;
    int y;
    BOOL continuous;
    int lineCount;
    int startX;
    u8 pad_18[0x24];
    int color;
} TextCursor;

typedef struct TextWindow {
    u8 pad_000[0x4];
    int style;
    u8 pad_008[0x34];
    u8 canvas[0x84 - 0x3c];
    int lineEnabled[10];
    int lineIndex;
    u8 pad_0b0[0x10c - 0xb0];
    TextCursor *cursor;
} TextWindow;

extern int ForwardInnerPayload_020018e4(void *canvas, int x, int y, int color, u16 glyph);
extern void FlushBufferAndRunCallback_0200153c(void *canvas);
extern int func_020019f4(void *canvas);

BOOL DrawNextTextGlyph_020bf0f0(TextWindow *window)
{
    TextCursor *cursor = window->cursor;
    int shadowColor;
    int width;
    int lineHeight;
    u16 ch;

    for (;;) {
        if (window->lineEnabled[window->lineIndex] == 0) {
            break;
        }
        while ((ch = *cursor->text) == 1 || ch == 2 || ch == 4) {
            switch (ch) {
            case 1:
                switch (window->style) {
                case 3:
                case 4:
                case 5:
                case 6:
                case 15:
                    cursor->color = 13;
                    break;
                case 14:
                    cursor->color = 9;
                    break;
                case 0:
                case 1:
                case 2:
                default:
                    cursor->color = 3;
                    break;
                }
                break;
            case 2:
                cursor->color = 7;
                break;
            case 4:
                cursor->color = 5;
                break;
            }
            cursor->text++;
        }
        shadowColor = 2;
        if (window->style == 14) {
            shadowColor = 8;
        }
        if (window->style == 15) {
            shadowColor = 14;
        }
        ForwardInnerPayload_020018e4(window->canvas, cursor->x + 1, cursor->y + 1, shadowColor, ch);
        width = ForwardInnerPayload_020018e4(window->canvas, cursor->x, cursor->y, cursor->color, *cursor->text);
        FlushBufferAndRunCallback_0200153c(window->canvas);
        if (*cursor->text != 10) {
            cursor->x += width;
            cursor->text++;
        }
        lineHeight = func_020019f4(window->canvas);
        while (*cursor->text == 10) {
            if (++cursor->lineCount >= 4) {
                return TRUE;
            }
            cursor->text++;
            cursor->x = cursor->startX;
            cursor->y += lineHeight + 2;
        }
        if (*cursor->text == 0) {
            return TRUE;
        }
        if (cursor->continuous != 0) {
            continue;
        }
        goto stalled;
    }
    return TRUE;
stalled:
    return FALSE;
}
