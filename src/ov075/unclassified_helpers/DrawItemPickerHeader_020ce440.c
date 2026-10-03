#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct {
    u8 pad_0000[0x608];
    u8 tiles[0x9c40 - 0x608];
    s16 hSpace;
    s16 vSpace;
} TextPanel;

typedef struct {
    u8 pad_00[0x40];
    const u16 *name;
} ItemDef;

typedef struct {
    u8 pad_00[8];
    ItemDef *def;
} ItemSlot;

typedef struct {
    u8 pad_00000[0x3c18];
    ItemSlot *slots[0x45b];
    s16 slotCount;
    s16 cursor;
    u8 pad_4d88[0x4e5c - 0x4d88];
    u8 messageTable[1];
} ItemPicker;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern void *func_ov027_020ba2a8(void *table, int idx);

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace, int vSpace)
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

static inline void DrawText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt)
{
    G2D_DrawAnchoredText_02017dec(pTxn, x, y, cl, flags, txt, GetFontDirection(pTxn->pFont));
}

void DrawItemPickerHeader_020ce440(ItemPicker *picker, TextPanel *panel, int width, int height)
{
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;

    G2D_InitializeLinearCanvas_02017a2c(&charCanvas, panel->tiles, width, height, NNS_G2D_CHARA_COLORMODE_256);
    charCanvas.vtable->pClear(&charCanvas, 0xf1);
    InitTextCanvas(&textCanvas, &charCanvas, func_ov039_020bc994(), panel->hSpace, panel->vSpace);
    DrawText(&textCanvas, (width * 8) / 2, 0, 0xfe, 0x10, picker->slots[picker->cursor]->def->name);
    DrawText(&textCanvas, (width * 8) / 2, 0xe, 0xf2, 0x10, func_ov027_020ba2a8(picker->messageTable, 3));
}
