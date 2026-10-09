#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct {
    u8 data[0x34];
} TextLayer;

typedef struct {
    u8 pad_000[0x990];
    TextLayer titleLayer;
    TextLayer infoLayer;
    TextLayer rowLayers[3];
    TextLayer labelLayer;
    TextLayer subLabelLayer;
    TextLayer detailLayer;
    TextLayer footerLayer;
    int textBank[3];
    u8 pad_b70[0xbc8 - 0xb70];
    u32 lockedId;
} PanelScene;

extern const TextFrame data_ov087_020c7cdc;
extern const char data_ov087_020c7e7c[];
extern void *UpdateScreenWidgetLayer_020bc1e4(int widget);
extern void LoadPackedFileView_020ba25c(int *view, const char *path, BOOL fromTail);
extern void *func_ov039_020bc994(void);
extern void InitTextLayerAt_020014b0(TextLayer *layer, int bgLayer, void *screenBase, void *font, TextFrame *frame);
extern void RefreshSelectedEntryInfo_020c5ef0(PanelScene *scene, BOOL playSound);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern const u16 *func_02051f48(u32 id, int variant);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern void *func_ov027_020ba2a8(int *table, int index);
extern void SetScreenLayerDirty_020bc104(int layerId);

void InitPanelTextLayers_020c663c(PanelScene *scene)
{
    TextFrame frame = data_ov087_020c7cdc;
    void *screen = UpdateScreenWidgetLayer_020bc1e4(10);
    BOOL i;

    i = 0;
    LoadPackedFileView_020ba25c(scene->textBank, data_ov087_020c7e7c, FALSE);
    InitTextLayerAt_020014b0(&scene->infoLayer, 2, screen, func_ov039_020bc994(), &frame);
    RefreshSelectedEntryInfo_020c5ef0(scene, FALSE);
    frame.x = 0xe;
    frame.width = 0x12;
    frame.y = 0;
    frame.charBase += 0x20;
    frame.height = 2;
    InitTextLayerAt_020014b0(&scene->titleLayer, 2, screen, func_ov039_020bc994(), &frame);
    CallVirtualHandlerSlot1_02001574(&scene->titleLayer, 0);
    DrawTextAnchored_020015a0(&scene->titleLayer, 0x8e, 2, 2, 0x821, func_02051f48(scene->lockedId, -1));
    Text_UploadTileBuffer_02001520(&scene->titleLayer);
    frame.x = 8;
    frame.y = 0x11;
    frame.width = 0x10;
    frame.charBase += 0x24;
    frame.height = 2;
    for (; i < 3; i++) {
        InitTextLayerAt_020014b0(&scene->rowLayers[i], 2, screen, func_ov039_020bc994(), &frame);
        frame.y += 2;
        frame.charBase += 0x20;
    }
    frame.x = 3;
    frame.y = 0x14;
    frame.width = 0xc;
    frame.height = 2;
    InitTextLayerAt_020014b0(&scene->labelLayer, 2, NULL, func_ov039_020bc994(), &frame);
    CallVirtualHandlerSlot1_02001574(&scene->labelLayer, 0);
    DrawTextAnchored_020015a0(&scene->labelLayer, 0x30, 2, 2, 0x411, func_ov027_020ba2a8(scene->textBank, 0xb));
    Text_UploadTileBuffer_02001520(&scene->labelLayer);
    frame.x = 0x11;
    frame.charBase += 0x18;
    InitTextLayerAt_020014b0(&scene->subLabelLayer, 2, NULL, func_ov039_020bc994(), &frame);
    DrawTextAnchored_020015a0(&scene->subLabelLayer, 0x30, 2, 2, 0x411, func_ov027_020ba2a8(scene->textBank, 0xc));
    Text_UploadTileBuffer_02001520(&scene->subLabelLayer);
    frame.x = 1;
    frame.vSpace = 1;
    frame.width = 0x1e;
    frame.y = 0xc;
    frame.height = 0xb;
    frame.charBase += 0x18;
    InitTextLayerAt_020014b0(&scene->detailLayer, 2, NULL, func_ov039_020bc994(), &frame);
    frame.height = 2;
    frame.x = 6;
    frame.y = 0xf;
    frame.charBase += 0x14a;
    frame.width = 0x14;
    frame.vSpace = 1;
    InitTextLayerAt_020014b0(&scene->footerLayer, 2, NULL, func_ov039_020bc994(), &frame);
    DrawTextAnchored_020015a0(&scene->footerLayer, 0x50, 2, 2, 0x411, func_ov027_020ba2a8(scene->textBank, 0x19));
    Text_UploadTileBuffer_02001520(&scene->footerLayer);
    SetScreenLayerDirty_020bc104(10);
}
