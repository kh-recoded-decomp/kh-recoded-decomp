#include "nitro/types.h"
#include "nnsys/g2d.h"

extern int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *pFont, int vSpace, const void *txt);
extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *pFont, u16 idx);

NNSG2dTextRect func_ov075_020cf2e8(const NNSG2dTextCanvas *txn, const u16 *text)
{
    int lineWidth = 0;
    NNSG2dTextRect rect = {0, 0};

    if (text != NULL && *text != 0) {
        rect.height = NNSi_G2dFontGetTextHeight_02016b4c(txn->pFont, txn->vSpace, text);
        do {
            u16 c = *text;
            if (c >= 0x20) {
                const NNSG2dFont *font = txn->pFont;
                u16 glyphIndex = G2D_FindGlyphIndex_02016a10(font, c);
                if (glyphIndex == 0xffff) {
                    glyphIndex = font->pRes->alterCharIndex;
                }
                lineWidth += G2D_GetGlyphWidths_02016a58(font, glyphIndex)->charWidth;
            } else if (c == '\n') {
                if (rect.width < lineWidth) {
                    rect.width = lineWidth;
                }
                lineWidth = 0;
            }
            text++;
        } while (*text != 0);
        if (rect.width < lineWidth) {
            rect.width = lineWidth;
        }
    }
    return rect;
}
