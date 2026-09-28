#include "nitro/types.h"

typedef struct {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct {
    u8 pad_00[8];
    u32 itemId;
    s32 slotId;
    u8 pad_10[0x18];
    u16 flags;
    u16 unk_2A;
    u8 pad_2C[0x10];
} FieldEntry;

typedef struct {
    u8 pad_000[0xB0];
    FieldEntry *slots;
    u8 pad_0B4[4];
    NNSFndList list;
    u8 pad_0C4[0x28];
    s32 selectedIndex;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *FND_GetListObjectByIndex_02012a64(NNSFndList *list, u16 index);
extern void InsertIntrusiveListObject_02012974(NNSFndList *list, void *where, void *object);
extern void RemoveIntrusiveListObject_020129d8(NNSFndList *list, void *object);
extern void func_ov001_020769f4(FieldMenu *menu);

void func_ov001_020785c0(s32 slotId, u16 value)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldEntry *current = FND_GetListObjectByIndex_02012a64(&menu->list, menu->selectedIndex);
    FieldEntry *slot;
    s32 index;
    u16 itemId;

    current->unk_2A = 0;
    itemId = current->itemId;
    current->itemId = 0xFFFF;
    current->flags |= 8;
    current->flags &= ~1;
    for (index = 0; index < 14; index++) {
        slot = &menu->slots[index];
        if (slot->slotId == slotId) {
            slot->unk_2A = value;
            slot->itemId = itemId;
            slot->flags &= ~8;
            slot->flags |= 1;
            InsertIntrusiveListObject_02012974(&menu->list, current, slot);
            RemoveIntrusiveListObject_020129d8(&menu->list, current);
            break;
        }
    }
    func_ov001_020769f4(menu);
}
