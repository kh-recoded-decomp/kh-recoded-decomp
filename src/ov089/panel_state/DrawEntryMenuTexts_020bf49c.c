#include "nitro/types.h"
#include "nnsys/g2d.h"

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

typedef struct TextLayer {
    u8 pad_00[0x14];
    NNSG2dFont *font;
    u8 pad_18[4];
    int vSpace;
    u8 pad_20[0x14];
} TextLayer;

typedef struct GameState {
    u8 pad_0000[0x28d4];
    s8 world;
    s8 column;
} GameState;

typedef struct Ov089Menu {
    u8 pad_000[0x744];
    int entryCount;
    u8 pad_748[0x3c];
    TextLayer captionLayer;
    TextLayer titleLayer;
    TextLayer headerLayer;
    TextLayer labelLayerA;
    TextLayer labelLayerB;
    TextLayer pageLayer;
    TextLayer hintLayer;
    u8 messages[4];
} Ov089Menu;

extern GameState *data_0205fe0c;
extern const TextFrame data_ov089_020c0510;
extern u16 data_ov089_020c062c[];
extern u16 data_ov089_020c0634[];
extern char data_ov089_020c063c[];
extern u16 data_ov089_020c0654[];

extern u16 *UpdateScreenWidgetLayer_020bc1e4(int widget);
extern void SetScreenLayerDirty_020bc104(int layerId);
extern u32 func_0202b788(void);
extern void LoadPackedFileView_020ba25c(void *view, const char *path, BOOL fromTail);
extern NNSG2dFont *func_ov039_020bc994(void);
extern u32 func_ov039_020bc9ac(void);
extern BOOL InitTextLayerAt_020014b0(TextLayer *layer, int bgLayer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame);
extern void RefreshEntryCaption_020beff4(Ov089Menu *menu, BOOL playSound);
extern int GetGridTableValue_02051f48(int row, int column);
extern int OS_SNPrintf_0202e080(u16 *dst, u32 len, const u16 *fmt, ...);
extern void CallVirtualHandlerSlot1_02001574(TextLayer *layer, int arg);
extern void func_0200160c(TextLayer *layer, u32 x, u32 y, u32 color, u32 flags, u16 *text, u32 overrideValue, int maxWidth);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const void *text);
extern int NNSi_G2dFontGetTextHeight_02016b4c(const NNSG2dFont *font, int vSpace, const void *text);
extern void DrawCenteredTextLine_02001768(TextLayer *layer, int unused, int y, int color, int altColor, int shadowColor, void *text, BOOL shadow);

void DrawEntryMenuTexts_020bf49c(Ov089Menu *menu)
{
    TextFrame frame = data_ov089_020c0510;
    u16 title[0x40];
    u16 *screen;
    u16 *separator;
    int world;
    int name;
    int height;
    void *text;

    screen = UpdateScreenWidgetLayer_020bc1e4(10);
    world = data_0205fe0c->world;
    if (func_0202b788() == 2) {
        separator = data_ov089_020c062c;
    } else {
        separator = data_ov089_020c0634;
    }
    LoadPackedFileView_020ba25c(menu->messages, data_ov089_020c063c, FALSE);
    InitTextLayerAt_020014b0(&menu->captionLayer, 2, screen, func_ov039_020bc994(), &frame);
    RefreshEntryCaption_020beff4(menu, FALSE);
    name = GetGridTableValue_02051f48(world, -1);
    OS_SNPrintf_0202e080(title, 0x40, data_ov089_020c0654, name, separator, GetGridTableValue_02051f48(world, data_0205fe0c->column));

    frame.x = 0xe;
    frame.y = 0;
    frame.height = 2;
    frame.width = 0x12;
    frame.charBase += 0x20;
    InitTextLayerAt_020014b0(&menu->titleLayer, 2, screen, func_ov039_020bc994(), &frame);
    CallVirtualHandlerSlot1_02001574(&menu->titleLayer, 0);
    func_0200160c(&menu->titleLayer, 0x8e, 2, 2, 0x821, title, func_ov039_020bc9ac(), 0x8e);
    Text_UploadTileBuffer_02001520(&menu->titleLayer);

    frame.x = 8;
    frame.y = 0x12;
    frame.width = 0x10;
    frame.height = 2;
    frame.charBase += 0x24;
    InitTextLayerAt_020014b0(&menu->headerLayer, 2, screen, func_ov039_020bc994(), &frame);
    if (func_0202b788() == 4) {
        DrawTextAnchored_020015a0(&menu->headerLayer, 0x41, 2, 2, 0x411, func_ov027_020ba2a8(menu->messages, 0));
    } else {
        DrawTextAnchored_020015a0(&menu->headerLayer, 0x40, 2, 2, 0x411, func_ov027_020ba2a8(menu->messages, 0));
    }
    Text_UploadTileBuffer_02001520(&menu->headerLayer);

    frame.x = 3;
    frame.y = 0x13;
    frame.width = 0xc;
    frame.height = 2;
    frame.charBase += 0x20;
    InitTextLayerAt_020014b0(&menu->labelLayerA, 2, NULL, func_ov039_020bc994(), &frame);
    CallVirtualHandlerSlot1_02001574(&menu->labelLayerA, 0);
    DrawTextAnchored_020015a0(&menu->labelLayerA, 0x30, 2, 2, 0x411, func_ov027_020ba2a8(menu->messages, 1));
    Text_UploadTileBuffer_02001520(&menu->labelLayerA);

    frame.x = 0x11;
    frame.charBase += 0x18;
    InitTextLayerAt_020014b0(&menu->labelLayerB, 2, NULL, func_ov039_020bc994(), &frame);
    DrawTextAnchored_020015a0(&menu->labelLayerB, 0x30, 2, 2, 0x411, func_ov027_020ba2a8(menu->messages, 2));
    Text_UploadTileBuffer_02001520(&menu->labelLayerB);

    frame.y = 0x16;
    frame.width = 0x1e;
    frame.x = 0;
    frame.vSpace = 0;
    frame.height = 2;
    frame.charBase += 0x18;
    InitTextLayerAt_020014b0(&menu->pageLayer, 2, screen, func_ov039_020bc994(), &frame);
    if (menu->entryCount > 1) {
        DrawTextAnchored_020015a0(&menu->pageLayer, 2, 4, 2, 0x209, func_ov027_020ba2a8(menu->messages, 3));
    }
    Text_UploadTileBuffer_02001520(&menu->pageLayer);

    frame.x = 1;
    frame.y = 0xc;
    frame.width = 0x1e;
    frame.height = 10;
    frame.vSpace = 0;
    frame.charBase += 0x3c;
    InitTextLayerAt_020014b0(&menu->hintLayer, 2, NULL, func_ov039_020bc994(), &frame);
    height = NNSi_G2dFontGetTextHeight_02016b4c(menu->hintLayer.font, menu->hintLayer.vSpace, func_ov027_020ba2a8(menu->messages, 5));
    DrawCenteredTextLine_02001768(&menu->hintLayer, 0x78, (0x50 - height) / 2, 2, 10, 6, func_ov027_020ba2a8(menu->messages, 5), FALSE);
    Text_UploadTileBuffer_02001520(&menu->hintLayer);
    SetScreenLayerDirty_020bc104(10);
}
