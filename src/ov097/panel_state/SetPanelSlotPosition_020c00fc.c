#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 data[0x6434];
} PanelList;

typedef struct {
    int panelIndex;
    int x;
    int y;
    u8 pad_0c[0x10];
} PanelSlot;

typedef struct {
    u8 pad_0000[0x218];
    PanelList panelLists[2];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

typedef struct {
    fx32 x;
    fx32 y;
} PanelPosition;

extern void func_0204f13c(void *recordBase, int recordIndex, PanelPosition *position);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void SetPanelSlotPosition_020c00fc(int listIndex, int slotIndex, int x, int y, MenuScene *scene)
{
    PanelList *list = &scene->panelLists[listIndex];
    PanelSlot *slot;
    PanelPosition position;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    slot->x = x;
    slot->y = y;
    position.x = ROW_TO_FX32(slot->x);
    position.y = ROW_TO_FX32(slot->y);
    func_0204f13c(list, slot->panelIndex, &position);
}
