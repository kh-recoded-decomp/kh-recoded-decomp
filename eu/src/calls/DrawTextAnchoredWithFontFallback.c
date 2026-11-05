#include "src/text/FontResources.h"

extern int GetTextLayerLineWidth(const TextLayerFontView *layer, const u16 *text,
                                 const u16 **nextLine);
extern void Obj_SetField14(TextLayerFontView *layer, NNSG2dFont *font);
extern void DrawTextAnchored(TextLayerFontView *layer, s32 x, s32 y, s32 color,
    u32 drawFlags, const u16 *text);

void DrawTextAnchoredWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, u32 drawFlags, const u16 *text,
    NNSG2dFont *fallbackFont, s32 maxWidth)
{
    const u16 *remaining;
    int width;
    int maxSeen;
    NNSG2dFont *defaultFont;

    remaining = text;
    defaultFont = layer->defaultFont;
    maxSeen = 0;
    do {
        width = GetTextLayerLineWidth(layer, remaining, &remaining);
        if (maxSeen < width) {
            maxSeen = width;
        }
    } while (remaining != NULL);
    if (maxSeen > maxWidth) {
        Obj_SetField14(layer, fallbackFont);
    }
    DrawTextAnchored(layer, x, y, color, drawFlags, text);
    /* Restore the layer default, even when the entry canvas font differed. */
    Obj_SetField14(layer, defaultFont);
}
