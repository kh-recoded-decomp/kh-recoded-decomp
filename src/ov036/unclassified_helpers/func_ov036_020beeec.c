#include "nitro/types.h"

#pragma opt_loop_invariants off

typedef struct {
    const u16 *text;
    s32 x;
    s32 y;
    s32 continueDrawing;
    s32 lineCount;
    s32 lineStartX;
    u8 pad_18[0x2C];
    s32 color;
} TextCursor;

typedef struct {
    u8 pad_00[0x04];
    s32 kind;
    u8 pad_08[0x34];
    u8 textLayer[0x48];
    s32 pageEnabled[10];
    s32 pageIndex;
    u8 pad_B0[0x5C];
    TextCursor *cursor;
} TextWindow;

extern int ForwardInnerPayload_020018e4(void *layer, int x, int y, int color, u16 glyph);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern int func_020019f4(void *layer);

BOOL func_ov036_020beeec(TextWindow *window)
{
    TextCursor *cursor = window->cursor;
    u16 glyph;
    int shadowColor;
    int advance;

    do {
        if (window->pageEnabled[window->pageIndex] == 0) {
            goto done;
        }
        while ((glyph = *cursor->text) == 1 || glyph == 2 || glyph == 4) {
            switch (glyph) {
            case 1:
                switch (window->kind) {
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
        if (window->kind == 14) {
            shadowColor = 8;
        }
        if (window->kind == 15) {
            shadowColor = 14;
        }
        ForwardInnerPayload_020018e4(window->textLayer, cursor->x + 1, cursor->y + 1, shadowColor, glyph);
        advance = ForwardInnerPayload_020018e4(window->textLayer, cursor->x, cursor->y, cursor->color, *cursor->text);
        FlushBufferAndRunCallback_0200153c(window->textLayer);
        if (*cursor->text != 10) {
            cursor->x += advance;
            cursor->text++;
        }
        advance = func_020019f4(window->textLayer);
        while (*cursor->text == 10) {
            cursor->lineCount++;
            if (cursor->lineCount >= 4) {
                return TRUE;
            }
            cursor->text++;
            cursor->x = cursor->lineStartX;
            cursor->y += advance + 2;
        }
        if (*cursor->text == 0) {
            return TRUE;
        }
    } while (cursor->continueDrawing != 0);
    goto stopped;
done:
    return TRUE;
stopped:
    return FALSE;
}
