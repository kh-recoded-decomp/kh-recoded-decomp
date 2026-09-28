#include "nitro/types.h"
#include "nnsys/g2d.h"

int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *pFont, int vSpace, const void *txt) {
    const void *pos = txt;
    NNSG2dTextRect rect = {0, 0};
    int lines = 1;
    NNSiG2dSplitCharCallback getNextChar = pFont->cbCharSpliter;
    u16 c;

    while ((c = getNextChar(&pos)) != 0) {
        if (c == '\n') {
            lines++;
        }
    }
    return lines * (vSpace + pFont->pRes->linefeed) - vSpace;
}
