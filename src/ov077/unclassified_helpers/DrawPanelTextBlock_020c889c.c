#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextPanel {
    u8 pad_0000[0x608];
    u8 tiles[0x9c30 - 0x608];
    u16 *text;
    u32 flags;
    u8 pad_9c38[6];
    u16 textColor;
    s16 hSpace;
    s16 vSpace;
} TextPanel;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight,
                                                NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *pFont, int vSpace, const void *txt);
extern int MeasureTextLine_020c8100(const NNSG2dTextCanvas *pTxn, const u16 *text, const u16 **next);
extern void DrawNnsG2dText_02017ff0(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *txt,
                                    NNSG2dTagCallback cbFunc, void *cbParam, NNSiG2dTextDirection d);
extern void func_ov077_020c8168(u16 tag, NNSG2dTagCallbackInfo *info);

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

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dTextCanvas *pTxn)
{
    return GetFontDirection(pTxn->pFont);
}

void DrawPanelTextBlock_020c889c(BOOL unused, TextPanel *panel, int width, int height)
{
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;
    u16 *cursor;
    u16 *text;
    int top;
    int x;

    if (width == 0 || height == 0) {
        return;
    }
    G2D_InitializeLinearCanvas_02017a2c(&charCanvas, panel->tiles, width, height, NNS_G2D_CHARA_COLORMODE_256);
    charCanvas.vtable->pClear(&charCanvas, 0xf1);
    InitTextCanvas(&textCanvas, &charCanvas, func_ov039_020bc994(), panel->hSpace, panel->vSpace);
    panel->textColor = 0xf2;
    text = panel->text;
    if (text == NULL) {
        return;
    }
    cursor = NULL;
    top = (height * 8 - NNSi_G2dFontGetTextHeight_02016b4c(textCanvas.pFont, textCanvas.vSpace, text)) / 2;
    if (panel->flags & 0x10) {
        x = (width * 8 - MeasureTextLine_020c8100(&textCanvas, text, NULL)) / 2;
        for (cursor = text; *cursor != 0; cursor++) {
            if (*cursor == '\n') {
                *cursor = 0x1f;
            }
        }
    } else {
        x = 0;
    }
    DrawNnsG2dText_02017ff0(&textCanvas, x, top, 0xf2, text, func_ov077_020c8168, panel,
                            GetTextDirection(&textCanvas));
    if (cursor != NULL) {
        for (cursor = text; *cursor != 0; cursor++) {
            if (*cursor == 0x1f) {
                *cursor = '\n';
            }
        }
    }
}
