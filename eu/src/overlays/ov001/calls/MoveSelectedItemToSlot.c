#include "nitro/types.h"

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct FieldEntry {
    u8 pad_00[8];
    u32 itemId;
    s32 slotId;
    u8 pad_10[0x18];
    u16 flags;
    u16 count;
    u8 pad_2c[0x10];
} FieldEntry;

typedef struct FieldMenu {
    u8 pad_000[0xb0];
    FieldEntry *slots;
    u8 pad_0b4[4];
    NNSFndList list;
    u8 pad_0c4[0x28];
    s32 selectedIndex;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 state;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern void *FND_GetListObjectByIndex(NNSFndList *list, u16 index);
extern void NNS_FndInsertListObject(
    NNSFndList *list,
    void *where,
    void *object
);
extern void NNS_FndRemoveListObject(NNSFndList *list, void *object);
extern void DrawMenuPanelPage(FieldMenu *menu);

void MoveSelectedItemToSlot(s32 slotId, u16 count)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    FieldEntry *current =
        FND_GetListObjectByIndex(&menu->list, menu->selectedIndex);
    FieldEntry *slot;
    s32 index;
    u16 itemId;

    current->count = 0;
    itemId = current->itemId;
    current->itemId = 0xffff;
    current->flags |= 8;
    current->flags &= ~1;
    for (index = 0; index < 14; index++) {
        slot = &menu->slots[index];
        if (slot->slotId == slotId) {
            slot->count = count;
            slot->itemId = itemId;
            slot->flags &= ~8;
            slot->flags |= 1;
            NNS_FndInsertListObject(&menu->list, current, slot);
            NNS_FndRemoveListObject(&menu->list, current);
            break;
        }
    }
    DrawMenuPanelPage(menu);
}
