#include "nitro/types.h"
#include "nnsys/g2d.h"

extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *font, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *font, u16 index);

int GetLineWidth_020011ec(const NNSG2dTextCanvas *canvas, const u16 *text, const u16 **nextLine)
{
    const NNSG2dFont *font = canvas->pFont;
    int hSpace = canvas->hSpace;
    int width = 0;
    int result;
    u16 c;

    while ((c = *text) != 0 && c != '\n' && c != 0x1f) {
        if (c >= 0x20) {
            u16 index = G2D_FindGlyphIndex_02016a10(font, c);
            if (index == NNS_G2D_GLYPH_INDEX_NOT_FOUND) {
                index = font->pRes->alterCharIndex;
            }
            width += hSpace + G2D_GetGlyphWidths_02016a58(font, index)->charWidth;
        }
        text++;
    }
    result = width - hSpace;
    if (result <= 0) {
        result = 0;
    }
    if (nextLine != NULL) {
        if (c == '\n') {
            *nextLine = text + 1;
            return result;
        }
        *nextLine = NULL;
    }
    return result;
}
