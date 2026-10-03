#include "nitro/types.h"

typedef struct TextLayer TextLayer;

extern void DrawTextAnchored_020015a0(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text);

void DrawShadowedText_020bf284(TextLayer *layer, int x, int y, const u16 *text, u8 color)
{
    DrawTextAnchored_020015a0(layer, x + 1, y + 1, color - 1, 0x20, text);
    DrawTextAnchored_020015a0(layer, x, y, color, 0x20, text);
}
