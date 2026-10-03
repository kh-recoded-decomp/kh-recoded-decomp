#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct NameSource {
    u8 pad_00[0x40];
    const void *text;
} NameSource;

typedef struct NameEntry {
    u8 pad_00[8];
    NameSource *source;
} NameEntry;

typedef struct MatrixMenu {
    u8 pad_0000[0x3c18];
    NameEntry *entries[1];
    u8 pad_3c1c[0x4d86 - 0x3c1c];
    s16 selectedEntry;
    u8 pad_4d88[0x4e5c - 0x4d88];
    int messageTable[1];
} MatrixMenu;

typedef struct TextPanel {
    u8 pad_0000[0x608];
    u8 tiles[0x9c40 - 0x608];
    s16 hSpace;
    s16 vSpace;
} TextPanel;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern NNSG2dFont *func_ov039_020bc994(void);
extern void *func_ov027_020ba2a8(int *table, int index);

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

static inline void DrawCanvasText(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt)
{
    G2D_DrawAnchoredText_02017dec(pTxn, x, y, cl, flags, txt, GetFontDirection(pTxn->pFont));
}

void DrawSelectedEntryName_020ce5c4(MatrixMenu *menu, TextPanel *panel, int width, int height)
{
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;

    G2D_InitializeLinearCanvas_02017a2c(&charCanvas, panel->tiles, width, height, NNS_G2D_CHARA_COLORMODE_256);
    charCanvas.vtable->pClear(&charCanvas, 0xf1);
    InitTextCanvas(&textCanvas, &charCanvas, func_ov039_020bc994(), panel->hSpace, panel->vSpace);
    DrawCanvasText(&textCanvas, (width * 8) / 2, 0, 0xfe, 0x10, menu->entries[menu->selectedEntry]->source->text);
    DrawCanvasText(&textCanvas, (width * 8) / 2, 0xe, 0xf2, 0x10, func_ov027_020ba2a8(menu->messageTable, 0x31));
}
