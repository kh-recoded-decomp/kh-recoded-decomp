#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct ItemInfo {
    u8 pad_00[0x40];
    const void *name;
} ItemInfo;

typedef struct ItemSlotEntry {
    u8 pad_00[0x8];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct ItemScreen {
    u8 pad_0000[0x3c18];
    ItemSlotEntry *list[0x45b];
    u16 pad_4d84;
    s16 listCursor;
    u8 pad_4d88[0x4e5c - 0x4d88];
    u8 messages[1];
} ItemScreen;

typedef struct MessageWindow {
    u8 pad_0000[0x608];
    u8 charBase[0x9c40 - 0x608];
    s16 hSpace;
    s16 vSpace;
} MessageWindow;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                                NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags,
                                          const void *txt, NNSiG2dTextDirection d);
extern void *func_ov027_020ba2a8(void *messages, int index);

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

void DrawItemNameUseHeader_020c7408(ItemScreen *screen, MessageWindow *window, int areaWidth, int areaHeight)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, window->charBase, areaWidth, areaHeight,
                                        NNS_G2D_CHARA_COLORMODE_256);
    canvas.vtable->pClear(&canvas, 0xf1);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), window->hSpace, window->vSpace);
    DrawCanvasText(&txn, areaWidth * 8 / 2, 0, 0xfe, 0x10, screen->list[screen->listCursor]->info->name);
    DrawCanvasText(&txn, areaWidth * 8 / 2, 0xe, 0xf2, 0x10, func_ov027_020ba2a8(screen->messages, 0x31));
}
