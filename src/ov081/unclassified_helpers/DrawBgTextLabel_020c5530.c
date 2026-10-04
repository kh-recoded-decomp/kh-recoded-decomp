#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef void (*LoadCharFunc)(const void *src, u32 offset, u32 size);
typedef u16 *(*GetScrPtrFunc)(void);

typedef struct LoadCharTable {
    LoadCharFunc func[4];
} LoadCharTable;

typedef struct ScrPtrTable {
    GetScrPtrFunc func[4];
} ScrPtrTable;

extern const LoadCharTable data_020c5c64;
extern const ScrPtrTable data_020c5c74;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                                NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern void DrawNnsG2dText_02017ff0(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *txt,
                                    NNSG2dTagCallback cbFunc, void *cbParam, NNSiG2dTextDirection d);
extern void func_ov081_020c5510(u16 c, NNSG2dTagCallbackInfo *cbInfo);
extern void func_0200344c(void *start, u32 size);
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

void DrawBgTextLabel_020c5530(void *charBase, int bg, const void *text, int x, int y, int areaWidth, int areaHeight, int tile)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    LoadCharTable loaders;
    ScrPtrTable scrPtrs;
    u32 size;
    u32 width = areaWidth;
    u32 height = areaHeight;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, charBase, width, height, NNS_G2D_CHARA_COLORMODE_256);
    canvas.vtable->pClear(&canvas, 0);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), 0, 1);
    DrawNnsG2dText_02017ff0(&txn, 0, 0, 0xf2, text, func_ov081_020c5510, NULL, GetFontDirection(txn.pFont));
    loaders = data_020c5c64;
    scrPtrs = data_020c5c74;
    size = areaWidth * 64 * areaHeight;
    func_0200344c(charBase, size);
    loaders.func[bg](charBase, tile << 6, size);
    FillBackgroundTileRectangle_02017adc(scrPtrs.func[bg](), width, height, x, y, 0x20, tile, 0);
}
