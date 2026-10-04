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
    TextWindow windows[3];
    u8 pad_a94[0xdc];
    PanelStackEntry stack[6];
    int depth;
    int selectedSlot;
} PanelScene;

typedef struct {
    int values[3];
} IdTriple;

extern const IdTriple data_ov087_020c7cc4;
extern u16 *func_ov039_020bc1e4(int bgId);
extern void *func_ov039_020bc1bc(void);
extern void FillBackgroundLayerRect_02001a60(void *layer, u16 *dst, int x, int y, u8 palette);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, BOOL visible);
extern void ApplySelectedSubitemValues_020b94fc(void *container, void *element, BOOL useAlt);
extern void SetScreenLayerDirty_020bc104(int layerId);

void ShowChoiceWindows_020c4b74(PanelScene *scene, int count)
{
    u16 *tileMap = func_ov039_020bc1e4(10);
    int i;
    IdTriple widgetIds = data_ov087_020c7cc4;
    void *container = func_ov039_020bc1bc();
    int widgetId;

    if (count > 3) {
        count = 3;
    }
    for (i = 0; i < count; i++) {
        if (scene->stack[scene->depth].stateId != 0x10) {
            FillBackgroundLayerRect_02001a60(&scene->windows[i], tileMap, 8, (u16)(i * 2 + 0x11), 0xf);
        }
        widgetId = widgetIds.values[i];
        func_ov027_020b9580(container, func_ov027_020b90a4(container, widgetId), TRUE);
        ApplySelectedSubitemValues_020b94fc(container, func_ov027_020b90a4(container, widgetId), TRUE);
    }
    SetScreenLayerDirty_020bc104(10);
    scene->selectedSlot = 0;
}



