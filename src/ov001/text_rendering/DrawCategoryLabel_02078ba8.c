#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct TextCanvas {
    u8 pad_00[0x24];
    u8 *pixels;
} TextCanvas;

typedef struct TextLayer {
    u8 pad_00[0x20];
    TextCanvas *canvas;
    u8 pad_24[0x10];
} TextLayer;

typedef struct LabelWork {
    u8 pad_0000[0x3240];
    u8 upperTiles[0x3c0];
    u8 lowerTiles[0x240];
} LabelWork;

extern const TextFrame data_ov001_0209df14;

extern u32 MakePrimaryVramKey_02073634(int index);
extern void LoadPackedFileView_020ba25c(MessageSet *messages, u32 key, int compressed);
extern int MapKindToCategory_02078b04(int kind);
extern const u16 *func_ov027_020ba2a8(MessageSet *messages, int index);
extern void *GetSceneFont_020711bc(void);
extern void InitTextLayerAt_020014b0(TextLayer *layer, int bgLayer, void *charBase, void *font, TextFrame *frame);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DestroyFndObjectList_020014f0(TextLayer *layer);
extern void FreePointerIfSet_020ba294(MessageSet *messages);

void DrawCategoryLabel_02078ba8(LabelWork *work, int kind)
{
    TextFrame frame = data_ov001_0209df14;
    TextLayer layer;
    MessageSet messages;
    const u16 *text;
    u8 *pixels;

    LoadPackedFileView_020ba25c(&messages, MakePrimaryVramKey_02073634(0), 1);
    text = func_ov027_020ba2a8(&messages, MapKindToCategory_02078b04(kind));
    InitTextLayerAt_020014b0(&layer, 1, NULL, GetSceneFont_020711bc(), &frame);
    pixels = layer.canvas->pixels;
    func_01ff878c(work->upperTiles, pixels, 0x240);
    func_01ff878c(work->lowerTiles, pixels + 0x240, 0x240);
    DrawTextAnchored_020015a0(&layer, 0x25, 5, 0xf1, 0x411, text);
    DrawTextAnchored_020015a0(&layer, 0x24, 4, 0xf2, 0x411, text);
    func_01ff878c(pixels, work->upperTiles, 0x240);
    func_01ff878c(pixels + 0x240, work->lowerTiles, 0x240);
    DestroyFndObjectList_020014f0(&layer);
    FreePointerIfSet_020ba294(&messages);
}
