#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef enum NNSG2dCharaColorMode {
    NNS_G2D_CHARA_COLORMODE_16 = 4,
    NNS_G2D_CHARA_COLORMODE_256 = 8
} NNSG2dCharaColorMode;

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct LabelSource {
    u8 unknown00[0x40];
    const void *text;
} LabelSource;

typedef struct LabelEntry {
    LabelSource *source;
    u8 unknown04[8];
} LabelEntry;

typedef struct SlotMenu {
    u8 unknown00000[0x824];
    LabelEntry labels[16];
    u8 unknown008E4[0x11ee8 - 0x8e4];
    s16 scrollRow;
    u8 unknown11EEA[0x1c6f8 - 0x11eea];
    u8 panelBackground[0x780];
    u8 widePanelBackground[0x780];
    u8 unknown1D5F8[0x1f1f8 - 0x1d5f8];
    u8 panelTiles[24][0x1c00];
} SlotMenu;

typedef char RecordEntryIsFourBytes[sizeof(RecordEntry) == 4 ? 1 : -1];
typedef char LabelEntryIsTwelveBytes[sizeof(LabelEntry) == 12 ? 1 : -1];
typedef char SlotMenuLabelsOffset[(u32)&((SlotMenu *)0)->labels == 0x824 ? 1 : -1];
typedef char SlotMenuScrollRowOffset[(u32)&((SlotMenu *)0)->scrollRow == 0x11ee8 ? 1 : -1];
typedef char SlotMenuTilesOffset[(u32)&((SlotMenu *)0)->panelTiles == 0x1f1f8 ? 1 : -1];

extern u16 gRankGlyphCodepoints[4];

extern int NNS_G2dCharCanvasDrawChar(const NNSG2dCharCanvas *canvas, const NNSG2dFont *font,
    int x, int y, int color, u16 character);
extern void *FormatStateText(int id, void *buffer, int flags, ...);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void NNS_G2dCharCanvasInitForBG(NNSG2dCharCanvas *canvas, void *tiles,
    int width, int height, NNSG2dCharaColorMode colorMode);
extern int NNSi_G2dFontGetTextWidth(const NNSG2dFont *font, int spacing, const void *text);
extern void NNSi_G2dTextCanvasDrawText(const NNSG2dTextCanvas *canvas,
    int x, int y, int color, u32 flags, const void *text, NNSiG2dTextDirection direction);
extern NNSG2dFont *GetMenuFont10(void);
extern NNSG2dFont *GetMenuFont10s(void);
extern void SlotMenu_UploadLabel(SlotMenu *menu, int slot, int part, u8 *tiles);

static inline NNSiG2dTextDirection GetFontDirection(const NNSG2dFont *font)
{
    NNSiG2dTextDirection direction = {0, 0};

    switch (font->pRes->pGlyph->flags) {
    case 0:
    case 7:
        direction.x = 1;
        break;
    case 1:
    case 2:
        direction.y = 1;
        break;
    case 3:
    case 4:
        direction.x = -1;
        break;
    case 5:
    case 6:
        direction.y = -1;
        break;
    }
    return direction;
}

static inline void DrawCanvasText(const NNSG2dTextCanvas *canvas,
    int x, int y, int color, u32 flags, const void *text)
{
    NNSi_G2dTextCanvasDrawText(canvas, x, y, color, flags, text, GetFontDirection(canvas->pFont));
}

/* Draw the record's name, rank marker and level into its slot-menu panel. */
void SlotMenu_DrawRecordLabel(SlotMenu *menu, int slot, int part, const RecordEntry *record)
{
    int row = slot - menu->scrollRow;
    int panelIndex;
    const void *text;
    u8 *tiles;
    int textWidth;
    unsigned kind;
    unsigned level;
    NNSG2dCharCanvas charCanvas;
    NNSG2dTextCanvas textCanvas;
    char levelText[16];

    if (row < -1 || row > 2) {
        return;
    }
    panelIndex = part + slot * 3;
    if (part == 2) {
        tiles = menu->panelTiles[panelIndex];
        MIi_CpuCopyFast(menu->widePanelBackground, tiles, sizeof(menu->widePanelBackground));
    } else {
        tiles = menu->panelTiles[panelIndex];
        MIi_CpuCopyFast(menu->panelBackground, tiles, sizeof(menu->panelBackground));
    }
    NNS_G2dCharCanvasInitForBG(&charCanvas, tiles, 15, 2, NNS_G2D_CHARA_COLORMODE_256);
    NNSG2dFont *font = GetMenuFont10();
    textCanvas.hSpace = 0;
    textCanvas.vSpace = 0;
    u8 category = (u8)record->category;
    textCanvas.pCanvas = &charCanvas;
    textCanvas.pFont = font;
    text = menu->labels[category].source->text;
    textWidth = NNSi_G2dFontGetTextWidth(textCanvas.pFont, 0, text);
    if (textWidth >= 0x45) {
        textCanvas.pFont = GetMenuFont10s();
        textWidth = NNSi_G2dFontGetTextWidth(textCanvas.pFont, textCanvas.hSpace, text);
    }
    DrawCanvasText(&textCanvas, 4, 5, 0xf3, 9, text);
    DrawCanvasText(&textCanvas, 3, 4, 0xf2, 9, text);

    kind = record->kind;
    if (kind != 0) {
        u16 glyph = gRankGlyphCodepoints[kind];
        NNS_G2dCharCanvasDrawChar(textCanvas.pCanvas, textCanvas.pFont, textWidth + 4, 5, 0xfb, glyph);
        NNS_G2dCharCanvasDrawChar(textCanvas.pCanvas, textCanvas.pFont, textWidth + 3, 4, 0xfa, glyph);
    }
    level = record->level;
    if (level != 0 && level < 100) {
        FormatStateText(1, levelText, 8, level);
        textCanvas.pFont = GetMenuFont10();
        DrawCanvasText(&textCanvas, 104, 5, 0xf3, 0x21, levelText);
        DrawCanvasText(&textCanvas, 103, 4, 0xf2, 0x21, levelText);
    }
    SlotMenu_UploadLabel(menu, slot, part, tiles);
}
