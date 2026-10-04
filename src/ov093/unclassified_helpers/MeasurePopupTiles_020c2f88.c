#include "nitro/types.h"

typedef struct {
    int width;
    int height;
} Size2D;

typedef struct {
    u8 pad_00[0x14];
    void *font;
    int hSpace;
    int vSpace;
    u8 pad_20[0x18];
} TextLayer;

typedef struct {
    u8 pad_00[0x18];
    TextLayer textLayer;
} PopupState;

typedef struct {
    u8 pad_00[8];
    void *font;
} PopupManager;

extern PopupManager *g_popupManager_020c50e4;
extern BOOL InitTextLayerDefault_02001494(TextLayer *layer, int layerIndex, void *font, void *frame);
extern Size2D G2D_MeasureTextRectangle_02016c18(void *font, int hSpace, int vSpace, const void *text);
extern void DestroyFndObjectList_020014f0(TextLayer *layer);

static inline Size2D MeasureLayerText(TextLayer *layer, const void *text)
{
    Size2D rect = G2D_MeasureTextRectangle_02016c18(layer->font, layer->hSpace, layer->vSpace, text);

    return rect;
}

Size2D MeasurePopupTiles_020c2f88(PopupState *popup, const void *text, void *frame, int padX, int padY)
{
    Size2D tiles;
    Size2D pixels;

    InitTextLayerDefault_02001494(&popup->textLayer, 6, g_popupManager_020c50e4->font, frame);
    pixels = MeasureLayerText(&popup->textLayer, text);
    pixels.width += padX;
    pixels.height += padY;
    tiles.width = pixels.width / 8;
    if (pixels.width % 8 > 0) {
        tiles.width++;
    }
    tiles.height = pixels.height / 8;
    if (pixels.height % 8 > 0) {
        tiles.height++;
    }
    if (tiles.width > 30) {
        tiles.width = 30;
    }
    if (tiles.height > 22) {
        tiles.height = 22;
    }
    DestroyFndObjectList_020014f0(&popup->textLayer);
    return tiles;
}
