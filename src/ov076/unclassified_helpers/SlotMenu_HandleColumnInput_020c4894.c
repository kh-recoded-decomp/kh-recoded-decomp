#include "nitro/types.h"

typedef struct PadInput {
    u8 pad_00[0xa];
    u16 repeat;
} PadInput;

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
} ScrollList;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    u32 column;
    u8 pad_00018[0x11ee4 - 0x18];
    ScrollList list;
} SlotMenu;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

extern SaveData *data_0205fe0c;
extern u16 data_02060500;

extern PadInput *func_ov039_020bca00(void);
extern BOOL func_ov039_020bc0d4(void);
extern void *func_ov039_020bc1bc(void);
extern void ScriptCmd_ResetScreenLayer_020be0c4(ScrollList *list, void *layout);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *layout);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern BOOL SlotMenu_IsSlotPairFilled_020c4560(SlotMenu *menu, int slot);
extern void SlotMenu_ShowSlotHint_020c827c(SlotMenu *menu);

static inline BOOL IsRecordHandle(u16 handle)
{
    return handle >= 0x200 && handle < 0x458;
}

void SlotMenu_HandleColumnInput_020c4894(SlotMenu *menu)
{
    BOOL blocked;
    PadInput *input = func_ov039_020bca00();
    u32 column = menu->column;
    u16 oldColumn = column;
    int slot = menu->list.slotIndex;
    u16 oldSlot = slot;

    if (input->repeat & 0x40) {
        if (column == 0) {
            int prev;

            if (slot == 0 && !(data_02060500 & 0x40)) {
                goto done;
            }
            if (slot == 0) {
                prev = menu->list.count - 1;
            } else {
                prev = slot - 1;
            }
            if (IsRecordHandle(data_0205fe0c->slotHandles[prev * 2])) {
                if (SlotMenu_IsSlotPairFilled_020c4560(menu, prev)) {
                    menu->column = 2;
                } else {
                    menu->column = 1;
                }
            } else {
                menu->column = 0;
            }
            goto done;
        } else {
            u16 handle = data_0205fe0c->slotHandles[slot * 2];

            menu->column = (column == 2 && IsRecordHandle(handle)) ? 1 : 0;
        }
    } else if (input->repeat & 0x80) {
        blocked = FALSE;

        if (column == 0) {
            if (IsRecordHandle(data_0205fe0c->slotHandles[slot * 2])) {
                menu->column = 1;
            } else {
                blocked = TRUE;
            }
        } else if (column == 1) {
            if (SlotMenu_IsSlotPairFilled_020c4560(menu, slot)) {
                menu->column = 2;
            } else {
                blocked = TRUE;
            }
        } else {
            blocked = TRUE;
        }
        if (blocked) {
            if (menu->list.slotIndex != menu->list.count - 1 || (data_02060500 & 0x80)) {
                menu->column = 0;
            }
            goto done;
        }
    } else {
        goto done;
    }
    PlaySoundEffect_0204d924(1, 0);
    input->repeat = 0;
done:
    if (func_ov039_020bc0d4()) {
        void *layout = func_ov039_020bc1bc();

        ScriptCmd_ResetScreenLayer_020be0c4(&menu->list, layout);
        RefreshScrollListLayout_020be138(&menu->list, layout);
        if (input->repeat & 0x30) {
            if (menu->column == 2 && !SlotMenu_IsSlotPairFilled_020c4560(menu, menu->list.slotIndex)) {
                menu->column = 1;
            }
            if (menu->column == 1 && !IsRecordHandle(data_0205fe0c->slotHandles[menu->list.slotIndex * 2])) {
                menu->column = 0;
            }
        }
    }
    if (oldColumn != menu->column || oldSlot != menu->list.slotIndex) {
        SlotMenu_ShowSlotHint_020c827c(menu);
    }
}
