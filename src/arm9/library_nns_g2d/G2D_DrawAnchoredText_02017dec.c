#include "nitro/types.h"
#include "nnsys/g2d.h"

#define TEXT_ORIGIN_MIDDLE 0x2
#define TEXT_ORIGIN_BOTTOM 0x4
#define TEXT_ORIGIN_CENTER 0x10
#define TEXT_ORIGIN_RIGHT 0x20

extern NNSG2dTextRect G2D_MeasureTextRectangle_02016c18(const NNSG2dFont *pFont, int hSpace, int vSpace, const void *txt);
extern void G2D_DrawAlignedText_02017c9c(const NNSG2dTextCanvas *pTxn, int x, int y, int areaWidth, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);

static inline NNSG2dTextRect GetCanvasTextRect(const NNSG2dTextCanvas *pTxn, const void *txt)
{
    NNSG2dTextRect rect = G2D_MeasureTextRectangle_02016c18(pTxn->pFont, pTxn->hSpace, pTxn->vSpace, txt);
    return rect;
}

void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d)
{
    NNSG2dTextRect rect = GetCanvasTextRect(pTxn, txt);

    if (flags & TEXT_ORIGIN_CENTER) {
        const int offset = -(rect.width + 1) / 2;
        x += offset * d.x;
        y += offset * d.y;
    } else if (flags & TEXT_ORIGIN_RIGHT) {
        const int offset = -rect.width;
        x += offset * d.x;
        y += offset * d.y;
    }

    if (flags & TEXT_ORIGIN_MIDDLE) {
        const int offset = -(rect.height + 1) / 2;
        x += offset * -d.y;
        y += offset * d.x;
    } else if (flags & TEXT_ORIGIN_BOTTOM) {
        const int offset = -rect.height;
        x += offset * -d.y;
        y += offset * d.x;
    }

    G2D_DrawAlignedText_02017c9c(pTxn, x, y, rect.width, cl, flags, txt, d);
}
