#include "nitro/types.h"
#include "nnsys/g2d.h"

extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *pFont, u16 idx);

static inline const u8 *GetGlyphImageFromIndex(const NNSG2dFont *pFont, u16 idx)
{
    const NNSG2dFontGlyph *pGlyph = pFont->pRes->pGlyph;
    return pGlyph->glyphTable + idx * pGlyph->cellSize;
}

static inline void GetGlyphFromIndex(NNSG2dGlyph *pGlyph, const NNSG2dFont *pFont, u16 idx)
{
    pGlyph->pWidths = G2D_GetGlyphWidths_02016a58(pFont, idx);
    pGlyph->image = GetGlyphImageFromIndex(pFont, idx);
}

static inline void GetGlyph(NNSG2dGlyph *pGlyph, const NNSG2dFont *pFont, u16 ccode)
{
    u16 idx = G2D_FindGlyphIndex_02016a10(pFont, ccode);
    if (idx == NNS_G2D_GLYPH_INDEX_NOT_FOUND) {
        idx = pFont->pRes->alterCharIndex;
    }
    GetGlyphFromIndex(pGlyph, pFont, idx);
}

int G2D_DrawCharGlyph_02017910(const NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ccode)
{
    NNSG2dGlyph glyph;
    const NNSG2dFontGlyph *pFontGlyph;

    GetGlyph(&glyph, pFont, ccode);
    pFontGlyph = pFont->pRes->pGlyph;

    switch (pFontGlyph->flags) {
    case 0:
    case 7:
        x += glyph.pWidths->left;
        break;
    case 1:
    case 2:
        x -= pFontGlyph->cellWidth;
        y += glyph.pWidths->left;
        break;
    case 3:
    case 4:
        x -= glyph.pWidths->left + glyph.pWidths->glyphWidth;
        y -= pFontGlyph->cellHeight;
        break;
    case 5:
    case 6:
        y -= glyph.pWidths->left + pFontGlyph->cellHeight;
        break;
    }

    pCC->vtable->pDrawGlyph(pCC, pFont, x, y, cl, &glyph);
    return glyph.pWidths->charWidth;
}
