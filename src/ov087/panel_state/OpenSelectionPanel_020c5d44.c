#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xb64];
    u8 labelTable[0x60];
    BOOL useAlternateFocus;
} PanelScene;

extern void *func_ov039_020bc1bc(void);
extern void func_ov087_020c4b74(PanelScene *scene, int mode);
extern void *func_ov027_020ba2a8(void *table, int index);
extern void func_ov087_020c4714(PanelScene *scene, int slotIndex, void *label, int mode);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b96e4(void *container, void *element);
extern void func_ov087_020c43c4(PanelScene *scene, void *element, int arg2, int arg3);

void OpenSelectionPanel_020c5d44(PanelScene *scene)
{
    void *container = func_ov039_020bc1bc();
    void *element;

    func_ov087_020c4b74(scene, 2);
    func_ov087_020c4714(scene, 0, func_ov027_020ba2a8(scene->labelTable, 2), 2);
    func_ov087_020c4714(scene, 1, func_ov027_020ba2a8(scene->labelTable, 3), 2);
    element = !scene->useAlternateFocus ? func_ov027_020b90a4(container, 2) : func_ov027_020b90a4(container, 3);
    func_ov027_020b96e4(container, element);
    func_ov087_020c43c4(scene, element, 0, 0);
}
