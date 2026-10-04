#include "nitro/types.h"

typedef struct {
    int resourceId;
    int animId;
    int x;
    int y;
    int flag;
    BOOL visible;
} PanelDesc;

typedef struct {
    int slotIndex;
    int x;
    int y;
    u8 pad_0c[0x8];
} ListPanel;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
} MenuScene;

extern int AllocObjSlot_0204f0b4(void *objManager, int resourceId, int animId);
extern void func_0204f204(void *objManager, int slotIndex, int value);
extern void func_0204f2e4(void *objManager, int slotIndex);
extern void func_0204f178(void *objManager, int slotIndex, int scale);
extern void Slot_SetMode2Bit_0204f480(void *objManager, int slotIndex, int value);
extern void func_0204f378(void *objManager, int slotIndex, int value);
extern int func_0204f2c0(void *objManager, int slotIndex);
extern void SetListPanelSlotPos_020bfaa0(int screen, int panelIndex, int x, int y, MenuScene *scene);

void CreateListPanelSlot_020bf950(int screen, int panelIndex, PanelDesc *desc, MenuScene *scene)
{
    u8 *objects = scene->screenObjects[screen];
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];
    int slot = AllocObjSlot_0204f0b4(objects, desc->resourceId, desc->animId);

    func_0204f204(objects, slot, 0);
    func_0204f2e4(objects, slot);
    func_0204f178(objects, slot, 0);
    Slot_SetMode2Bit_0204f480(objects, slot, 0);
    func_0204f378(objects, slot, desc->flag);
    if (desc->visible) {
        func_0204f2c0(objects, slot);
    }
    panel->slotIndex = slot;
    panel->x = desc->x;
    panel->y = desc->y;
    SetListPanelSlotPos_020bfaa0(screen, panelIndex, desc->x, desc->y, scene);
}
