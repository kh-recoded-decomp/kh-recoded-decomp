#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x7ec];
    u8 promptLayer[0x34];
    u8 yesLayer[0x34];
    u8 noLayer[0x34];
    u8 pad_888[0x74];
    BOOL confirmMode;
} Ov089Menu;

extern void *func_ov039_020bc1bc(void);
extern u16 *UpdateScreenWidgetLayer_020bc1e4(int screen);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void SetEntrySlotsVisible_020b9580(void *container, void *widget, BOOL visible);
extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void SetFocusedWidget_020b96e4(void *container, void *widget);
extern void *func_ov039_020bc618(void);
extern void MoveCursorToElement_020bef34(void *menu, void *element, BOOL playSound);

void SetPopupConfirmMode_020bfdac(Ov089Menu *menu, BOOL confirm)
{
    void *container = func_ov039_020bc1bc();
    u16 *tileMap = UpdateScreenWidgetLayer_020bc1e4(10);
    void *widget;

    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 2), !confirm);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 7), confirm);
    SetEntrySlotsVisible_020b9580(container, FindWidgetById_020b90a4(container, 8), confirm);
    CallStateWidget_020bc14c(10, 3, 0x12, 0x1a, 3);
    if (confirm) {
        FillBackgroundLayerRect_02001a60(menu->yesLayer, tileMap, 3, 0x13, 0xf);
        FillBackgroundLayerRect_02001a60(menu->noLayer, tileMap, 0x11, 0x13, 0xf);
        widget = FindWidgetById_020b90a4(container, 8);
    } else {
        FillBackgroundLayerRect_02001a60(menu->promptLayer, tileMap, 8, 0x12, 0xf);
        widget = FindWidgetById_020b90a4(container, 2);
    }
    SetFocusedWidget_020b96e4(container, widget);
    menu->confirmMode = confirm;
    MoveCursorToElement_020bef34(func_ov039_020bc618(), widget, FALSE);
}
