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
    u8 pad_0c4[4];
    s32 scrollIndex;
    u8 pad_0cc[0xc];
    s32 listedCount;
    u8 pad_0dc[0x28];
    s32 mode;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 state;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern void *GetSceneTagTracker(void);
extern BOOL IsFieldFlag8Set(void);
extern void NNS_FndAppendListObject(NNSFndList *list, void *object);
extern void DrawMenuPanelPage(FieldMenu *menu);
extern void func_ov001_02075e10(
    FieldMenu *menu,
    void *tracker,
    s32 mode
);

void AddItemToFieldSlot(s32 slotId, u32 itemId, u16 amount)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    s32 previousCount = menu->listedCount;
    void *tracker = GetSceneTagTracker();
    FieldEntry *slot;
    s32 index;
    s32 total;

    if (!IsFieldFlag8Set()) {
        return;
    }
    for (index = 0; index < 14; index++) {
        slot = &menu->slots[index];
        if (slot->slotId == slotId) {
            if (slot->count == 0) {
                menu->listedCount++;
                slot->flags &= ~8;
                slot->flags |= 1;
                slot->itemId = itemId;
                NNS_FndAppendListObject(&menu->list, slot);
                if (menu->mode == 1) {
                    menu->scrollIndex = menu->listedCount;
                }
            } else {
                slot->itemId = itemId;
            }
            total = slot->count + amount;
            if (total >= 99) {
                total = 99;
            }
            slot->count = total;
            DrawMenuPanelPage(menu);
            break;
        }
    }
    if (previousCount == 0) {
        func_ov001_02075e10(menu, tracker, menu->mode);
    }
}
