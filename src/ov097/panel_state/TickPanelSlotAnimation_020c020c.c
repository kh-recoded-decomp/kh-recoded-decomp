#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} PanelList;

typedef struct {
    int panelIndex;
    u8 pad_04[0x18];
} PanelSlot;

typedef struct {
    u8 pad_0000[0x218];
    PanelList panelLists[2];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

extern void func_0204f2e4(void *recordBase, int recordIndex);
extern void func_0204f204(void *base, int index, u16 frames);

void TickPanelSlotAnimation_020c020c(int listIndex, int slotIndex, int frames, MenuScene *scene)
{
    PanelList *list = &scene->panelLists[listIndex];
    PanelSlot *slot;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    func_0204f2e4(list, slot->panelIndex);
    func_0204f204(list, slot->panelIndex, frames);
}
