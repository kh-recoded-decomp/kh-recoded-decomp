#include "nitro/types.h"
#include "nnsys/g2d.h"

#define TEXT_ALIGN_CENTER 0x400
#define TEXT_ALIGN_RIGHT 0x800

extern int NNSi_G2dFontGetStringWidth_02016aa0(const NNSG2dFont *pFont, int hSpace, const void *str, const void **pPos);
extern void G2D_DrawTextLine_02017be8(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *str, const void **pNext, NNSiG2dTextDirection d);

void G2D_DrawAlignedText_02017c9c(const NNSG2dTextCanvas *pTxn, int x, int y, int areaWidth, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d)
{
    const int linefeed = pTxn->vSpace + pTxn->pFont->pRes->linefeed;
    const int lineStepX = linefeed * -d.y;
    const int lineStepY = linefeed * d.x;
    int lineCount = 0;
    const void *pos = txt;

    while (pos != NULL) {
        int lineX = x + lineCount * lineStepX;
        int lineY = y + lineCount * lineStepY;

        if (flags & TEXT_ALIGN_RIGHT) {
            const int width = NNSi_G2dFontGetStringWidth_02016aa0(pTxn->pFont, pTxn->hSpace, pos, NULL);
            const int offset = areaWidth - width;
            lineX += offset * d.x;
            lineY += offset * d.y;
        } else if (flags & TEXT_ALIGN_CENTER) {
            const int width = NNSi_G2dFontGetStringWidth_02016aa0(pTxn->pFont, pTxn->hSpace, pos, NULL);
            const int offset = (areaWidth + 1) / 2 - (width + 1) / 2;
            lineX += offset * d.x;
            lineY += offset * d.y;
        }

        G2D_DrawTextLine_02017be8(pTxn, lineX, lineY, cl, pos, &pos, d);
        lineCount++;
    }
}
