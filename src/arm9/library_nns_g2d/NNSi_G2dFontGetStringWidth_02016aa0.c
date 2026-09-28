#include "nitro/types.h"
#include "nnsys/g2d.h"

extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *pFont, u16 idx);

/* adapted CC0 shared C */
int NNSi_G2dFontGetStringWidth_02016aa0(const NNSG2dFont *pFont, int hSpace, const void *str, const void **pPos) {
    int width = 0;
    const void *pos = str;
    u16 c;
    NNSiG2dSplitCharCallback getNextChar = pFont->cbCharSpliter;

    while ((c = getNextChar((const void **)&pos)) != 0) {
        if (c == '\n') {
            break;
        }

        u16 idx = G2D_FindGlyphIndex_02016a10(pFont, c);
        if (idx == 0xffff) {
            idx = pFont->pRes->alterCharIndex;
        }
        const NNSG2dCharWidths *widths = G2D_GetGlyphWidths_02016a58(pFont, idx);
        width += hSpace + widths->charWidth;
    }

    if (pPos != NULL) {
        *pPos = (c == '\n') ? pos : NULL;
    }
    if (width > 0) {
        width -= hSpace;
    }
    return width;
}
