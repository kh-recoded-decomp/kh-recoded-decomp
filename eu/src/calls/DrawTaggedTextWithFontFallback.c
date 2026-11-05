#include "src/text/FontResources.h"

extern int GetTextLayerLineWidth(const TextLayerFontView *layer, const u16 *text,
                                 const u16 **nextLine);
extern void Obj_SetField14(TextLayerFontView *layer, NNSG2dFont *font);
extern void DrawTextColored(TextLayerFontView *layer, s32 x, s32 y, s32 color,
    s32 alternateColor, const u16 *text);

void DrawTaggedTextWithFontFallback(TextLayerFontView *layer,
    s32 x, s32 y, s32 color, s32 alternateColor, const u16 *text,
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
    DrawTextColored(layer, x, y, color, alternateColor, text);
    /* Restore the layer default, even when the entry canvas font differed. */
    Obj_SetField14(layer, defaultFont);
}
