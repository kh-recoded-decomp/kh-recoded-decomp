#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef union PanelSize {
    u32 packed;
    struct {
        s16 width;
        s16 height;
    } dim;
} PanelSize;

typedef struct MenuPanel {
    u8 pad_0000[0x608];
    u8 textChars[1];
} MenuPanel;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern NNSG2dTextRect func_ov076_020cb238(const NNSG2dTextCanvas *txn, const u16 *text);

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace, int vSpace)
{
    pTxn->pCanvas = pCC;
    pTxn->pFont = pFont;
    pTxn->hSpace = hSpace;
    pTxn->vSpace = vSpace;
}

PanelSize MenuPanel_MeasureMessage_020cb2b8(MenuPanel *panel, int style, const u16 *text)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas txn;
    NNSG2dTextRect rect;
    PanelSize size;

    G2D_InitializeLinearCanvas_02017a2c(&canvas, panel->textChars, 0x1c, 0x14, NNS_G2D_CHARA_COLORMODE_256);
    InitTextCanvas(&txn, &canvas, func_ov039_020bc994(), 0, 1);
    rect = func_ov076_020cb238(&txn, text);
    size.dim.width = (rect.width >> 3) + (u16)((rect.width & 7) ? 1 : 0);
    size.dim.height = (rect.height >> 3) + (u16)((rect.height & 7) ? 1 : 0);
    if (style == 2) {
        size.dim.height += 2;
        size.dim.width = size.dim.width < 0x1a ? 0x1a : size.dim.width;
    }
    if (size.dim.width == 0) {
        size.dim.width = 1;
    }
    if (size.dim.height == 0) {
        size.dim.height = 1;
    }
    size.dim.width += 2;
    size.dim.height += 2;
    size.dim.width += size.dim.width & 1;
    if (size.dim.width > 0x20) {
        size.dim.width = 0x20;
    }
    return size;
}
