#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef enum NNSG2dCharaColorMode {
    NNS_G2D_CHARA_COLORMODE_16 = 4,
    NNS_G2D_CHARA_COLORMODE_256 = 8
} NNSG2dCharaColorMode;

typedef struct ItemScreen {
    u8 unknown00000[0x12d04];
    u8 hintBackground[0x1000];
    u8 hintTiles[0x1000];
} ItemScreen;

typedef struct ItemHintState {
    u32 unknown;
    u32 colors[2];
} ItemHintState;

typedef char ItemHintStateIsTwelveBytes[sizeof(ItemHintState) == 12 ? 1 : -1];
typedef char ItemHintColorsOffset[(u32)&((ItemHintState *)0)->colors == 4 ? 1 : -1];
typedef char ItemHintTilesOffset[(u32)&((ItemScreen *)0)->hintTiles == 0x13d04 ? 1 : -1];
typedef char ItemHintCanvasSize[sizeof(NNSG2dCharCanvas) == 0x18 ? 1 : -1];
typedef char ItemHintTextCanvasSize[sizeof(NNSG2dTextCanvas) == 0x10 ? 1 : -1];

ItemHintState data_ov077_020ca3a0;

extern void MIi_CpuCopyFast(const void *source, void *destination, u32 size);
extern void NNS_G2dCharCanvasInitForBG(NNSG2dCharCanvas *canvas, void *tiles, int width, int height, NNSG2dCharaColorMode mode);
extern NNSG2dFont *GetMenuFont10(void);
extern int NNSi_G2dFontGetTextHeight(const NNSG2dFont *font, int spacing, const void *text);
extern void NNSi_G2dTextCanvasDrawTaggedText(const NNSG2dTextCanvas *canvas, int x, int y, int color,
    const void *text, NNSG2dTagCallback callback, void *context, NNSiG2dTextDirection direction);
/* Legacy symbol for the callback that selects each text tag's color. */
extern void SelectChooserValueByIndex(u16 tag, NNSG2dTagCallbackInfo *info);
extern void DC_FlushRange(const void *start, u32 size);
extern void GX_LoadBG3Char(const void *tiles, u32 offset, u32 size);
extern u16 *G2_GetBG3ScrPtr(void);
extern void NNS_G2dMapScrToCharText(u16 *screen, int width, int height, int x, int y, int screenWidth, int charOffset, int palette);

static inline const NNSG2dFont *CanvasFont(const NNSG2dTextCanvas *canvas)
{
    return canvas->pFont;
}

static inline u8 GlyphOrientation(const NNSG2dFont *font)
{
    return font->pRes->pGlyph->flags;
}

static inline int MeasureCanvasTextHeight(const NNSG2dTextCanvas *canvas, const void *text)
{
    return NNSi_G2dFontGetTextHeight(canvas->pFont, canvas->vSpace, text);
}

static inline void InitTextCanvas(NNSG2dTextCanvas *textCanvas, NNSG2dCharCanvas *charCanvas, NNSG2dFont *font, int hSpace, int vSpace)
{
    textCanvas->pCanvas = charCanvas;
    textCanvas->pFont = font;
    textCanvas->hSpace = hSpace;
    textCanvas->vSpace = vSpace;
}

static inline NNSiG2dTextDirection GetTextDirection(const NNSG2dFont *font)
{
    NNSiG2dTextDirection direction = {0, 0};
    switch (GlyphOrientation(font)) {
    case 0:
    case 7:
        direction.x = 1;
        break;
    case 2:
    case 1:
        direction.y = 1;
        break;
    case 4:
    case 3:
        direction.x = -1;
        break;
    case 6:
    case 5:
        direction.y = -1;
        break;
    }
    return direction;
}

static inline void DrawHintText(const NNSG2dTextCanvas *canvas, int x, int y, int color,
    const void *text, NNSG2dTagCallback callback, void *context)
{
    NNSi_G2dTextCanvasDrawTaggedText(canvas, x, y, color, text,
        callback, context, GetTextDirection(CanvasFont(canvas)));
}

/* Restore the item menu background, then draw its hint into BG3. */
void ItemScreen_DrawHintText(ItemScreen *menu, const void *text)
{
    NNSG2dCharCanvas canvas;
    NNSG2dTextCanvas textCanvas;

    MIi_CpuCopyFast(menu->hintBackground, menu->hintTiles, sizeof(menu->hintTiles));
    NNS_G2dCharCanvasInitForBG(&canvas, menu->hintTiles, 32, 2, NNS_G2D_CHARA_COLORMODE_256);
    InitTextCanvas(&textCanvas, &canvas, GetMenuFont10(), 0, 1);
    if (text != NULL) {
        const int textHeight = MeasureCanvasTextHeight(&textCanvas, text);
        data_ov077_020ca3a0.colors[0] = 0xf2;
        data_ov077_020ca3a0.colors[1] = 0xfa;
        DrawHintText(&textCanvas, 3, 15 - textHeight, data_ov077_020ca3a0.colors[0], text,
            SelectChooserValueByIndex, data_ov077_020ca3a0.colors);
    }
    DC_FlushRange(menu->hintTiles, sizeof(menu->hintTiles));
    GX_LoadBG3Char(menu->hintTiles, 0xc000, sizeof(menu->hintTiles));
    NNS_G2dMapScrToCharText(G2_GetBG3ScrPtr(), 32, 2, 0, 22, 32, 0x300, 0);
}
