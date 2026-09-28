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
    u16 count;
    u8 pad_2C[0x10];
} FieldEntry;

typedef struct {
    u8 pad_000[0xB0];
    FieldEntry *slots;
    u8 pad_0B4[4];
    NNSFndList list;
    u8 pad_0C4[4];
    s32 unk_C8;
    u8 pad_0CC[0xC];
    s32 listedCount;
    u8 pad_0DC[0x28];
    s32 mode;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *GetSceneTagTracker_020711b0(void);
extern BOOL func_ov001_020728a4(void);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, void *object);
extern void func_ov001_020769f4(FieldMenu *menu);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);

void func_ov001_02078500(s32 slotId, u32 itemId, u16 amount)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    s32 previousCount = menu->listedCount;
    void *tracker = GetSceneTagTracker_020711b0();
    FieldEntry *slot;
    s32 index;
    s32 total;

    if (!func_ov001_020728a4()) {
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
                AppendIntrusiveListObject_020128d0(&menu->list, slot);
                if (menu->mode == 1) {
                    menu->unk_C8 = menu->listedCount;
                }
            } else {
                slot->itemId = itemId;
            }
            total = slot->count + amount;
            if (total >= 99) {
                total = 99;
            }
            slot->count = total;
            func_ov001_020769f4(menu);
            break;
        }
    }
    if (previousCount == 0) {
        func_ov001_02075e10(menu, tracker, menu->mode);
    }
}
