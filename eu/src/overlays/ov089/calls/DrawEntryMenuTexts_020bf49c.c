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
extern const TextFrame data_ov089_020c0530;
extern u16 data_ov089_020c064c[];
extern u16 data_ov089_020c0654[];
extern char sOv089_UiMenuStrLanguageCsSZ_020c065c[];
extern u16 data_ov089_020c0674[];

extern u16 *UpdateScreenWidgetLayer(int widget);
extern void SetScreenLayerDirty(int layerId);
extern u32 GetLanguageIndex(void);
extern void LoadPackedFileView(void *view, const char *path, BOOL fromTail);
extern NNSG2dFont *GetMenuFont10(void);
extern u32 GetMenuFont10s(void);
extern BOOL InitTextLayerAt(TextLayer *layer, int bgLayer, u16 *screenBase, NNSG2dFont *font, TextFrame *frame);
extern void RefreshEntryCaption(Ov089Menu *menu, BOOL playSound);
extern int GetGridTableValue(int row, int column);
extern int OS_SNPrintf_0202e094(u16 *dst, u32 len, const u16 *fmt, ...);
extern void CallVirtualHandlerSlot1(TextLayer *layer, int arg);
extern void func_02001620(TextLayer *layer, u32 x, u32 y, u32 color, u32 flags, u16 *text, u32 overrideValue, int maxWidth);
extern void Text_UploadTileBuffer(TextLayer *layer);
extern void *func_ov027_020ba2c8(void *messages, int index);
extern void DrawTextAnchored(TextLayer *layer, int x, int y, int color, u32 flags, const void *text);
extern int NNSi_G2dFontGetTextHeight(const NNSG2dFont *font, int vSpace, const void *text);
extern void DrawCenteredTextLine(TextLayer *layer, int unused, int y, int color, int altColor, int shadowColor, void *text, BOOL shadow);

void DrawEntryMenuTexts_020bf49c(Ov089Menu *menu)
{
    TextFrame frame = data_ov089_020c0530;
    u16 title[0x40];
    u16 *screen;
    u16 *separator;
    int world;
    int name;
    int height;
    void *text;

    screen = UpdateScreenWidgetLayer(10);
    world = data_0205fe0c->world;
    if (GetLanguageIndex() == 2) {
        separator = data_ov089_020c064c;
    } else {
        separator = data_ov089_020c0654;
    }
    LoadPackedFileView(menu->messages, sOv089_UiMenuStrLanguageCsSZ_020c065c, FALSE);
    InitTextLayerAt(&menu->captionLayer, 2, screen, GetMenuFont10(), &frame);
    RefreshEntryCaption(menu, FALSE);
    name = GetGridTableValue(world, -1);
    OS_SNPrintf_0202e094(title, 0x40, data_ov089_020c0674, name, separator, GetGridTableValue(world, data_0205fe0c->column));

    frame.x = 0xe;
    frame.y = 0;
    frame.height = 2;
    frame.width = 0x12;
    frame.charBase += 0x20;
    InitTextLayerAt(&menu->titleLayer, 2, screen, GetMenuFont10(), &frame);
    CallVirtualHandlerSlot1(&menu->titleLayer, 0);
    func_02001620(&menu->titleLayer, 0x8e, 2, 2, 0x821, title, GetMenuFont10s(), 0x8e);
    Text_UploadTileBuffer(&menu->titleLayer);

    frame.x = 8;
    frame.y = 0x12;
    frame.width = 0x10;
    frame.height = 2;
    frame.charBase += 0x24;
    InitTextLayerAt(&menu->headerLayer, 2, screen, GetMenuFont10(), &frame);
    if (GetLanguageIndex() == 4) {
        DrawTextAnchored(&menu->headerLayer, 0x41, 2, 2, 0x411, func_ov027_020ba2c8(menu->messages, 0));
    } else {
        DrawTextAnchored(&menu->headerLayer, 0x40, 2, 2, 0x411, func_ov027_020ba2c8(menu->messages, 0));
    }
    Text_UploadTileBuffer(&menu->headerLayer);

    frame.x = 3;
    frame.y = 0x13;
    frame.width = 0xc;
    frame.height = 2;
    frame.charBase += 0x20;
    InitTextLayerAt(&menu->labelLayerA, 2, NULL, GetMenuFont10(), &frame);
    CallVirtualHandlerSlot1(&menu->labelLayerA, 0);
    DrawTextAnchored(&menu->labelLayerA, 0x30, 2, 2, 0x411, func_ov027_020ba2c8(menu->messages, 1));
    Text_UploadTileBuffer(&menu->labelLayerA);

    frame.x = 0x11;
    frame.charBase += 0x18;
    InitTextLayerAt(&menu->labelLayerB, 2, NULL, GetMenuFont10(), &frame);
    DrawTextAnchored(&menu->labelLayerB, 0x30, 2, 2, 0x411, func_ov027_020ba2c8(menu->messages, 2));
    Text_UploadTileBuffer(&menu->labelLayerB);

    frame.y = 0x16;
    frame.width = 0x1e;
    frame.x = 0;
    frame.vSpace = 0;
    frame.height = 2;
    frame.charBase += 0x18;
    InitTextLayerAt(&menu->pageLayer, 2, screen, GetMenuFont10(), &frame);
    if (menu->entryCount > 1) {
        DrawTextAnchored(&menu->pageLayer, 2, 4, 2, 0x209, func_ov027_020ba2c8(menu->messages, 3));
    }
    Text_UploadTileBuffer(&menu->pageLayer);

    frame.x = 1;
    frame.y = 0xc;
    frame.width = 0x1e;
    frame.height = 10;
    frame.vSpace = 0;
    frame.charBase += 0x3c;
    InitTextLayerAt(&menu->hintLayer, 2, NULL, GetMenuFont10(), &frame);
    height = NNSi_G2dFontGetTextHeight(menu->hintLayer.font, menu->hintLayer.vSpace, func_ov027_020ba2c8(menu->messages, 5));
    DrawCenteredTextLine(&menu->hintLayer, 0x78, (0x50 - height) / 2, 2, 10, 6, func_ov027_020ba2c8(menu->messages, 5), FALSE);
    Text_UploadTileBuffer(&menu->hintLayer);
    SetScreenLayerDirty(10);
}
