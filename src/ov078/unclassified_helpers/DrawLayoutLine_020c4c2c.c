#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct LayoutEntry {
    int charBase;
    int tileX;
    int tileY;
    int width;
    int height;
    int textX;
    int textY;
    int color;
    u32 flags;
} LayoutEntry;

typedef struct PageMenu {
    u8 pad_00[0x50];
    u8 charBuffer[1];
} PageMenu;

extern LayoutEntry data_ov078_020c5004[];

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                                NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern int NNSi_G2dFontGetStringWidth_02016aa0(const NNSG2dFont *pFont, int hSpace, const void *str, const void **pPos);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags,
                                          const void *txt, NNSiG2dTextDirection d);
extern void func_0200344c(void *start, u32 size);
extern void GX_LoadBG2Char_02007a90(const void *src, u32 offset, u32 size);
extern void *G2_GetBG2ScrPtr_02006e88(void);
extern void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y, int mapW, int tile,
                                                 int palette);

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace,
                                  int vSpace)
{
    pTxn->pCanvas = pCC;
    pTxn->pFont = pFont;
    pTxn->hSpace = hSpace;
    pTxn->vSpace = vSpace;
}

static inline NNSiG2dTextDirection GetFontDirection(const NNSG2dFont *pFont)
{
    NNSiG2dTextDirection d = {0, 0};

    switch (pFont->pRes->pGlyph->flags) {
    case 0:
    case 7:
        d.x = 1;
        break;
    case 1:
    case 2:
        d.y = 1;
        break;
    case 3:
    case 4:
        d.x = -1;
        break;
    case 5:
    case 6:
        d.y = -1;
        break;
    }
    return d;
}

static inline void DrawCanvasText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt)
{
    G2D_DrawAnchoredText_02017dec(pTxn, x, y, cl, flags, txt, GetFontDirection(pTxn->pFont));
}

void DrawLayoutLine_020c4c2c(PageMenu *menu, int line, const void *text, const void *suffix)
{
    LayoutEntry *layout = &data_ov078_020c5004[line];
    BOOL narrow = FALSE;
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    int width;
    u32 size;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, menu->charBuffer, layout->width, layout->height,
                                        NNS_G2D_CHARA_COLORMODE_16);
    canvas.vtable->pClear(&canvas, 0);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), 0, 0);
    width = NNSi_G2dFontGetStringWidth_02016aa0(txn.pFont, 0, text, NULL);
    if (line == 0) {
        if (width >= 0xac) {
            narrow = TRUE;
        }
    } else if ((u32)(line - 5) <= 1 && width >= 0x30) {
        narrow = TRUE;
    }
    if (narrow) {
        txn.pFont = func_ov039_020bc9ac();
    }
    DrawCanvasText(&txn, layout->textX, layout->textY, layout->color, layout->flags, text);
    if (suffix != NULL) {
        u32 flags = (layout->flags & ~8) | 0x20;
        if (narrow) {
            txn.pFont = func_ov039_020bc994();
        }
        DrawCanvasText(&txn, layout->width << 3, layout->textY, layout->color, flags, suffix);
    }
    size = layout->width * 32 * layout->height;
    func_0200344c(menu->charBuffer, size);
    GX_LoadBG2Char_02007a90(menu->charBuffer, layout->charBase << 5, size);
    FillBackgroundTileRectangle_02017adc(G2_GetBG2ScrPtr_02006e88(), layout->width, layout->height, layout->tileX,
                                         layout->tileY, 0x20, layout->charBase, 0xf);
}
