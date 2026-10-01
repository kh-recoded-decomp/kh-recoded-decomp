#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct LabelSource {
    u8 pad_00[0x40];
    const void *text;
} LabelSource;

typedef struct LabelEntry {
    LabelSource *source;
    u8 pad_04[8];
} LabelEntry;

typedef struct SlotMenu {
    u8 pad_00000[0x824];
    LabelEntry labels[16];
    u8 pad_008E4[0x11ee8 - 0x8e4];
    s16 scrollRow;
    u8 pad_11EEA[0x1c6f8 - 0x11eea];
    u8 panelBackground[0x780];
    u8 widePanelBackground[0x780];
    u8 pad_1D5F8[0x1f1f8 - 0x1d5f8];
    u8 panelTiles[24][0x1c00];
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2dc0];
    u32 slotNumbers[8];
} SaveData;

extern SaveData *data_0205fe0c;
extern const char data_ov076_020cd350[];

extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern int G2D_MeasureTextWidth_02016bc0(const NNSG2dFont *pFont, int hSpace, const void *txt);
extern void G2D_DrawAnchoredText_02017dec(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, u32 flags, const void *txt, NNSiG2dTextDirection d);
extern int OS_SNPrintf_0202e080(char *dst, u32 len, const char *fmt, ...);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dFont *func_ov039_020bc9ac(void);
extern void func_ov076_020c7b44(SlotMenu *menu, int slot, int part, u8 *tiles);

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

void SlotMenu_DrawPanelLabel_020c7edc(SlotMenu *menu, int slot, int part, int labelIndex)
{
    int row = slot - menu->scrollRow;
    int panelIndex;
    const void *text;
    int numberX;
    u8 *tiles;
    int offset;
    u16 numberText[4];
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;

    if (row < -1 || row > 2) {
        return;
    }
    panelIndex = part + slot * 3;
    if (part == 2) {
        tiles = menu->panelTiles[panelIndex];
        func_01ff878c(menu->widePanelBackground, tiles, sizeof(menu->widePanelBackground));
    } else {
        tiles = menu->panelTiles[panelIndex];
        func_01ff878c(menu->panelBackground, tiles, sizeof(menu->panelBackground));
    }
    G2D_InitializeLinearCanvas_02017a2c(&charCanvas, tiles, 15, 2, NNS_G2D_CHARA_COLORMODE_256);
    InitTextCanvas(&textCanvas, &charCanvas, func_ov039_020bc994(), 0, 0);
    text = menu->labels[labelIndex].source->text;
    if (G2D_MeasureTextWidth_02016bc0(textCanvas.pFont, 0, text) >= 0x62) {
        textCanvas.pFont = func_ov039_020bc9ac();
    }
    DrawCanvasText(&textCanvas, 4, 5, 0xf3, 9, text);
    DrawCanvasText(&textCanvas, 3, 4, 0xf2, 9, text);

    offset = 0x10;
    if (part != 2) {
        offset = 0;
    }
    numberX = 0x78 - offset;
    OS_SNPrintf_0202e080((char *)numberText, 4, data_ov076_020cd350, data_0205fe0c->slotNumbers[slot]);
    numberText[3] = 0;
    textCanvas.pFont = func_ov039_020bc994();
    DrawCanvasText(&textCanvas, numberX, 5, 0xf3, 0x21, numberText);
    DrawCanvasText(&textCanvas, numberX - 1, 4, 0xf2, 0x21, numberText);
    func_ov076_020c7b44(menu, slot, part, tiles);
}
