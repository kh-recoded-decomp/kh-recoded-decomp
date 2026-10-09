#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    int lineGap;
    u8 pad_20[0x48];
} TextLayer;

typedef struct {
    u8 pad_000[0xafc];
    TextLayer promptLayer;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int bgId);
extern int func_020019f4(TextLayer *layer);
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void DrawCenteredTextLine_02001768(TextLayer *layer, int unused, int y, int color, int altColor, int shadowColor, u16 *text, BOOL shadow);
extern void Text_UploadTileBuffer_02001520(void *surface);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void *FindWidgetById_020b90a4(void *container, int elementId);
extern void SetEntrySlotsVisible_020b9580(void *container, void *element, BOOL visible);

void DrawCenteredPromptText_020c4860(PanelScene *scene, u16 *text)
{
    void *container = func_ov039_020bc1bc();
    u16 *tileMap = UpdateScreenWidgetLayer_020bc1e4(10);
    u16 *cursor = text;
    int height = func_020019f4(&scene->promptLayer);
    int lineStep = height + scene->promptLayer.lineGap;

    do {
        if (*cursor == '\n') {
            height += lineStep;
        }
    } while (*cursor++ != 0);
    CallVirtualHandlerSlot1_02001574(&scene->promptLayer, 0);
    DrawCenteredTextLine_02001768(&scene->promptLayer, 0x78, (0x65 - height) / 2 + 4, 2, 6, 10, text, FALSE);
    Text_UploadTileBuffer_02001520(&scene->promptLayer);
    FillBackgroundLayerRect_02001a60(&scene->promptLayer, tileMap, 1, 0xc, 0xf);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0), FALSE);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xe), TRUE);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 0xb), TRUE);
}
