#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct Ov082State {
    u8 pad_0000[0xd4];
    u8 rowTiles[9][0x600];
} Ov082State;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                                NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern const void *func_ov081_020c5bf8(int entry);
extern void func_01ff88c4(void *dst, int value, u32 size);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags,
                                          const void *txt, NNSiG2dTextDirection d);
extern void func_0200344c(void *start, u32 size);
extern void GFXi_EnqueueCommand_02014090(int command, u32 offset, const void *src, u32 size);
extern u16 *G2S_GetBG1ScrPtr_02006e68(void);
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

void DrawEntryRowText_020bf08c(Ov082State *state, int row, u8 entry, int indent)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    u16 scratch[0x30];
    const void *text;
    int width;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, state->rowTiles[row], 0x18, 2, NNS_G2D_CHARA_COLORMODE_16);
    canvas.vtable->pClear(&canvas, 0);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), 0, 1);
    text = func_ov081_020c5bf8(entry);
    func_01ff88c4(scratch, 0, sizeof(scratch));
    if (text == NULL) {
        return;
    }
    width = G2D_MeasureTextWidth_02016bc0(txn.pFont, txn.hSpace, text);
    if (width + indent * 5 >= 0xbc) {
        txn.pFont = func_ov039_020bc9ac();
    }
    DrawCanvasText(&txn, indent * 5, 0, 2, 9, text);
    func_0200344c(state->rowTiles[row], 0x600);
    GFXi_EnqueueCommand_02014090(0x15, row * 0x600 + 0x1a00, state->rowTiles[row], 0x600);
    FillBackgroundTileRectangle_02017adc(G2S_GetBG1ScrPtr_02006e68(), 0x18, 2, 4, row * 2 + 4, 0x20, row * 0x30 + 0xd0,
                                         0xf);
}
