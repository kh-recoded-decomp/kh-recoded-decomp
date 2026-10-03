#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextPanel {
    u8 pad_0000[0x608];
    u8 tiles[0x9c30 - 0x608];
    const u16 *text;
    u8 pad_9c34[4];
    u32 flags;
    u8 pad_9c3c[2];
    u16 textColor;
    s16 hSpace;
    s16 vSpace;
} TextPanel;

extern void G2D_InitializeLinearCanvas_02017a2c(NNSG2dCharCanvas *pCC, void *charBase, int areaWidth, int areaHeight, NNSG2dCharaColorMode colorMode);
extern NNSG2dFont *func_ov039_020bc994(void);
extern int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *pFont, int vSpace, const void *txt);
extern u16 G2D_FindGlyphIndex_02016a10(const NNSG2dFont *pFont, u16 c);
extern const NNSG2dCharWidths *G2D_GetGlyphWidths_02016a58(const NNSG2dFont *pFont, u16 idx);
extern void DrawNnsG2dText_02017ff0(const NNSG2dTextCanvas *pTxn, int x, int y, int cl, const void *txt, NNSG2dTagCallback cbFunc, void *cbParam, NNSiG2dTextDirection d);
extern void func_ov076_020cb134(u16 tag, NNSG2dTagCallbackInfo *info);

static inline void InitTextCanvas(NNSG2dTextCanvas *pTxn, NNSG2dCharCanvas *pCC, NNSG2dFont *pFont, int hSpace, int vSpace)
{
    pTxn->pCanvas = pCC;
    pTxn->pFont = pFont;
    pTxn->hSpace = hSpace;
    pTxn->vSpace = vSpace;
}

static inline int GetCharWidth(const NNSG2dFont *pFont, u16 c)
{
    u16 index = G2D_FindGlyphIndex_02016a10(pFont, c);

    if (index == NNS_G2D_GLYPH_INDEX_NOT_FOUND) {
        index = pFont->pRes->alterCharIndex;
    }
    return G2D_GetGlyphWidths_02016a58(pFont, index)->charWidth;
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

void MessageWindow_DrawLines_020cb9a0(BOOL leftAligned, TextPanel *panel, int width, int height)
{
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;
    u16 line[64];
    const u16 *text;
    u16 *out;
    int textHeight;
    int top;
    int lineIndex;
    int lineSpacing;
    int lineHeight;
    int areaWidth;
    int lineWidth;
    int x;
    u16 color;
    NNSiG2dTextDirection direction;

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
    textHeight = NNSi_G2dFontGetTextHeight_02016b4c(textCanvas.pFont, textCanvas.vSpace, text);
    top = (height * 8 - textHeight) / 2;
    lineIndex = 0;
    lineSpacing = panel->vSpace;
    lineHeight = lineSpacing + 10;
    if (*text != 0) {
        areaWidth = width * 8;
        do {
            lineWidth = 0;
            out = line;
            while (*text != '\n' && *text != 0) {
                if (*text >= 0x20) {
                    lineWidth += GetCharWidth(textCanvas.pFont, *text);
                }
                *out++ = *text++;
            }
            *out = 0;
            color = panel->textColor;
            direction = GetTextDirection(&textCanvas);
            if (leftAligned) {
                x = 0;
            } else {
                x = (areaWidth - lineWidth) / 2;
            }
            DrawNnsG2dText_02017ff0(&textCanvas, x, top + lineIndex * lineHeight, color, line, func_ov076_020cb134, panel, direction);
            if (*text != 0) {
                text++;
                lineIndex++;
            }
        } while (*text != 0);
    }
    panel->flags &= ~8;
}
