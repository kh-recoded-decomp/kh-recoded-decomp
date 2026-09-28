#include "nitro/types.h"
#include "nnsys/g2d.h"

extern int func_02017910(NNSG2dCharCanvas *pCC, const NNSG2dFont *pFont, int x, int y, int cl, u16 ch);

void G2D_DrawTextLine_02017be8(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *str, const void **pNext, NNSiG2dTextDirection d)
{
    const NNSG2dFont *pFont = pTxn->pFont;
    const void *pos = str;
    NNSiG2dSplitCharCallback getNextChar = pFont->cbCharSpliter;
    const int hSpace = pTxn->hSpace;
    u16 c;

    while ((c = getNextChar(&pos)) != 0) {
        int w;
        if (c == '\n') {
            break;
        }
        w = hSpace + func_02017910(pTxn->pCanvas, pFont, x, y, cl, c);
        x += w * d.x;
        y += w * d.y;
    }

    if (pNext != NULL) {
        *pNext = (c == '\n') ? pos : NULL;
    }
}
