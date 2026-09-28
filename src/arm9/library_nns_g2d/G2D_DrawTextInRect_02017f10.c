#include "nitro/types.h"
#include "nnsys/g2d.h"

#define TEXT_VALIGN_MIDDLE 0x80
#define TEXT_VALIGN_BOTTOM 0x100

extern int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *pFont, int vSpace, const void *txt);
extern void G2D_DrawAlignedText_02017c9c(const NNSG2dTextCanvas *pTxn, int x, int y, int areaWidth, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);

void G2D_DrawTextInRect_02017f10(const NNSG2dTextCanvas *pTxn, int x, int y, int areaWidth, int areaHeight, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d)
{
    if (flags & TEXT_VALIGN_BOTTOM) {
        const int height = NNSi_G2dFontGetTextHeight_02016b4c(pTxn->pFont, pTxn->vSpace, txt);
        const int offset = areaHeight - height;
        x += offset * -d.y;
        y += offset * d.x;
    } else if (flags & TEXT_VALIGN_MIDDLE) {
        const int height = NNSi_G2dFontGetTextHeight_02016b4c(pTxn->pFont, pTxn->vSpace, txt);
        const int offset = (areaHeight + 1) / 2 - (height + 1) / 2;
        x += offset * -d.y;
        y += offset * d.x;
    }

    G2D_DrawAlignedText_02017c9c(pTxn, x, y, areaWidth, cl, flags, txt, d);
}
