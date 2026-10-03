#include "nitro/types.h"
#include "nnsys/g2d.h"

extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *pFont, u16 idx);

int TextCanvas_GetLineWidth_020cb0cc(const NNSG2dTextCanvas *pTxn, const u16 *str, const u16 **pNext)
{
    const NNSG2dFont *pFont = pTxn->pFont;
    int hSpace = pTxn->hSpace;
    int width = 0;
    int result;
    u16 c;

    while ((c = *str) != 0 && c != '\n' && c != 0x1f) {
        if (c >= 0x20) {
            u16 idx = G2D_FindGlyphIndex_02016a10(pFont, c);

            if (idx == 0xffff) {
                idx = pFont->pRes->alterCharIndex;
            }
            width += hSpace + G2D_GetGlyphWidths_02016a58(pFont, idx)->charWidth;
        }
        str++;
    }
    result = width - hSpace;
    if (result <= 0) {
        result = 0;
    }
    if (pNext != NULL) {
        if (c == '\n') {
            *pNext = str + 1;
            return result;
        }
        *pNext = NULL;
    }
    return result;
}
