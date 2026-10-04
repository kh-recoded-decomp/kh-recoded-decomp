#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} PanelList;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} PanelRect;

typedef struct {
    int panelIndex;
    int x;
    int y;
    int width;
    int height;
    PanelRect rect;
} PanelSlot;

typedef struct {
    u8 pad_0000[0x218];
    PanelList panelLists[2];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

typedef struct {
    int resourceA;
    int resourceB;
    int x;
    int y;
    int flag;
    BOOL highlighted;
    u32 scale;
} PanelSlotDesc;

extern int func_0204f0b4(void *list, int resourceA, int resourceB);
extern void func_0204f204(void *list, int index, int frames);
extern void func_0204f2e4(void *list, int index);
extern void Slot_SetMode2Bit_0204f480(void *list, int index, int value);
extern void func_0204f378(void *list, int index, int value);
extern void func_0204f178(void *list, int index, int scale);
extern int func_0204f2c0(void *list, int index);
extern void SetPanelSlotPosition_020c00fc(int listIndex, int slotIndex, int x, int y, MenuScene *scene);
extern PanelRect *GetPanelSlotRecordData_020c0264(int listIndex, int slotIndex, MenuScene *scene);
extern void func_01ff89a8(const void *src, void *dst, u32 size);

void BindPanelSlot_020bffd0(int listIndex, int slotIndex, PanelSlotDesc *desc, MenuScene *scene)
{
    PanelList *list = &scene->panelLists[listIndex];
    PanelSlot *slot;
    PanelRect *rect;
    int panelIndex;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    panelIndex = func_0204f0b4(list, desc->resourceA, desc->resourceB);
    func_0204f204(list, panelIndex, 0);
    func_0204f2e4(list, panelIndex);
    Slot_SetMode2Bit_0204f480(list, panelIndex, 0);
    func_0204f378(list, panelIndex, desc->flag);
    func_0204f178(list, panelIndex, desc->scale & 0xff);
    if (desc->highlighted) {
        func_0204f2c0(list, panelIndex);
    }
    slot->panelIndex = panelIndex;
    slot->x = desc->x;
    slot->y = desc->y;
    SetPanelSlotPosition_020c00fc(listIndex, slotIndex, desc->x, desc->y, scene);
    rect = GetPanelSlotRecordData_020c0264(listIndex, slotIndex, scene);
    slot->width = rect->left - rect->right + 1;
    slot->height = rect->top - rect->bottom + 1;
    func_01ff89a8(rect, &slot->rect, sizeof(PanelRect));
}
