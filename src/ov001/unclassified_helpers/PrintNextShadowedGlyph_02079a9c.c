#include "nitro/types.h"

#pragma opt_loop_invariants off

typedef struct {
    u8 pad_00[0x3c];
    u16 *cursor;
    s32 x;
    s32 y;
    u8 pad_48[0x50 - 0x48];
    s32 color;
    u8 pad_54[0x94 - 0x54];
    u8 font[1];
} TextPrinter;

extern int ForwardInnerPayload_020018e4(void *font, int x, int y, int color, u16 glyph);
extern int func_020019f4(void *font);

BOOL PrintNextShadowedGlyph_02079a9c(TextPrinter *printer) {
    BOOL result;
    int lineHeight;
    u16 glyph;

    while ((glyph = *printer->cursor) == 1 || glyph == 2 || glyph == 4) {
        switch (glyph) {
        case 1:
            printer->color = 8;
            break;
        case 2:
            printer->color = 10;
            break;
        case 4:
            printer->color = 6;
            break;
        }
        printer->cursor++;
    }
    ForwardInnerPayload_020018e4(printer->font, printer->x + 1, printer->y + 1, printer->color - 1, glyph);
    printer->x += ForwardInnerPayload_020018e4(printer->font, printer->x, printer->y, printer->color, *printer->cursor);
    printer->cursor++;
    lineHeight = func_020019f4(printer->font);
    while ((glyph = *printer->cursor) == 10) {
        printer->cursor++;
        printer->x = 0;
        printer->y += lineHeight + 3;
    }
    result = FALSE;
    if (glyph != 0) {
        result = TRUE;
    }
    return result;
}
