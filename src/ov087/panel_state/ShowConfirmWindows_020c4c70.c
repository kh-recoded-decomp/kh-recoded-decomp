#include "nitro/types.h"

typedef struct {
    u8 data[0x34];
} TextWindow;

typedef struct {
    int stateId;
    void *focusElement;
} PanelStackEntry;

typedef struct {
    u8 pad_000[0x9f8];
    TextWindow choiceWindows[3];
    TextWindow confirmWindows[2];
    u8 pad_afc[0x74];
    PanelStackEntry stack[6];
    int depth;
    int selectedSlot;
} PanelScene;

typedef struct {
    int values[2];
} IdPair;

extern const IdPair data_ov087_020c7c80;
extern u16 *func_ov039_020bc1e4(int bgId);
extern void *func_ov039_020bc1bc(void);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void SetScreenLayerDirty_020bc104(int layerId);
extern void SetFocusedWidget_020b96e4(void *container, void *widget);
extern void MoveCursorToWidget_020c43c4(PanelScene *scene, void *widget, BOOL narrow, BOOL playSound);

void ShowConfirmWindows_020c4c70(PanelScene *scene)
{
    u16 *tileMap = func_ov039_020bc1e4(10);
    int i;
    IdPair widgetIds = data_ov087_020c7c80;
    void *container = func_ov039_020bc1bc();
    void *widget;

    for (i = 0; i < 2; i++) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect_02001a60(&scene->confirmWindows[i], tileMap, (u16)(i * 0xe + 3), 0x14, 0xf);
        }
        func_ov027_020b9580(container, func_ov027_020b90a4(container, widgetIds.values[i]), TRUE);
    }
    SetScreenLayerDirty_020bc104(10);
    widget = func_ov027_020b90a4(container, 8);
    SetFocusedWidget_020b96e4(container, widget);
    MoveCursorToWidget_020c43c4(scene, widget, TRUE, FALSE);
    scene->selectedSlot = 1;
}
