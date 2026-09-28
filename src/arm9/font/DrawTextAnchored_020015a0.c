#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 pad_00[0x10];
    NNSG2dTextCanvas txn;
} TextLayer;

extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);

void DrawTextAnchored_020015a0(TextLayer *obj, int x, int y, int color, u32 flags, const u16 *text)
{
    NNSG2dFont *font = obj->txn.pFont;
    NNSiG2dTextDirection dir = {0, 0};

    switch (font->pRes->pGlyph->flags) {
    case 0:
    case 7:
        dir.x = 1;
        break;
    case 1:
    case 2:
        dir.y = 1;
        break;
    case 3:
    case 4:
        dir.x = -1;
        break;
    case 5:
    case 6:
        dir.y = -1;
        break;
    }
    G2D_DrawAnchoredText_02017dec(&obj->txn, x, y, color, flags, text, dir);
}
