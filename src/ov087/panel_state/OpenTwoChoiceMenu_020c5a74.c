#include "nitro/types.h"

typedef struct {
    int values[2];
} IdPair;

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0xc];
} PanelScene;

extern const IdPair data_ov087_020c7c70;
extern void *func_ov039_020bc1bc(void);
extern void func_ov087_020c4b74(PanelScene *scene, int count);
extern void *func_ov027_020ba2a8(void *table, int index);
extern void func_ov087_020c4714(PanelScene *scene, int windowIndex, void *text, int color);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void SetFocusedWidget_020b96e4(void *container, void *widget);
extern void func_ov087_020c43c4(PanelScene *scene, void *widget, int slot, BOOL immediate);

void OpenTwoChoiceMenu_020c5a74(PanelScene *scene)
{
    void *container = func_ov039_020bc1bc();
    IdPair labels = data_ov087_020c7c70;
    void *widget;
    int i;

    func_ov087_020c4b74(scene, 2);
    for (i = 0; i < 2; i++) {
        func_ov087_020c4714(scene, i, func_ov027_020ba2a8(scene->labelTable, labels.values[i]), 2);
    }
    widget = func_ov027_020b90a4(container, 3);
    SetFocusedWidget_020b96e4(container, widget);
    func_ov087_020c43c4(scene, widget, 0, 0);
}
