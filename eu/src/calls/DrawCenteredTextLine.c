#include "nitro/types.h"

#pragma opt_propagation off

typedef struct TextLayer TextLayer;

extern int func_0200191c(TextLayer *layer, u16 *text, int flags);
extern void DrawTextColored(TextLayer *obj, int x, int y, int color, int altColor, const u16 *text);

void DrawCenteredTextLine(TextLayer *layer, int unused, int y, int color, int altColor, int shadowColor, u16 *text, BOOL shadow)
{
    u16 *cursor = text;
    int width = *(u16 *)((u8 *)layer + 0x2e) * 8;
    int x = (width + 1) / 2 - (func_0200191c(layer, cursor, 0) + 1) / 2;

    for (; *cursor != 0; cursor++) {
        if (*cursor == '\n') {
            *cursor = 0x1f;
        }
    }
    cursor = text;
    if (shadow) {
        DrawTextColored(layer, x + 1, y + 1, ((shadowColor - 1) << 8) | (color - 1), altColor - 1, cursor);
    }
    DrawTextColored(layer, x, y, color | (shadowColor << 8), altColor, cursor);
    for (; *cursor != 0; cursor++) {
        if (*cursor == 0x1f) {
            *cursor = '\n';
        }
    }
}
