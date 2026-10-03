#include "nitro/types.h"

typedef struct CursorMarker {
    u8 pad_00[2];
    s8 direction;
    u8 pad_03;
    s16 x;
    s16 y;
} CursorMarker;

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06;
    u8 visibleCount;
    u8 rowHeight;
    u8 pad_09[0x34 - 9];
    s32 scrollY;
} ScrollList;

typedef struct SlotMenu {
    u8 pad_00000[0x14];
    u32 column;
    u8 pad_00018[0x11ee4 - 0x18];
    ScrollList list;
} SlotMenu;

extern CursorMarker data_ov076_020cd260;
extern void *func_ov039_020bc1bc(void);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *layout);
extern void SlotMenu_ReloadVisibleSlots_020c7144(SlotMenu *menu);

void SlotMenu_MoveCursorToSlot_020c52f8(SlotMenu *menu, int slot, u32 column, int mode, CursorMarker *cursor)
{
    s16 offset = slot - menu->list.topSlot;
    s16 newTop = -1;
    s16 xOffset;
    s16 base;

    if (cursor == &data_ov076_020cd260) {
        newTop = slot;
    }
    if (offset <= 0) {
        cursor->direction = 1;
        if (offset < 0) {
            newTop = slot;
        }
    } else {
        cursor->direction = -1;
        if (offset > 1 || cursor == &data_ov076_020cd260) {
            newTop = slot - 1;
        }
    }
    if (newTop >= 0) {
        if (newTop + menu->list.visibleCount > menu->list.count) {
            newTop = menu->list.count - menu->list.visibleCount;
        }
        menu->list.topSlot = newTop;
        menu->list.scrollY = newTop * menu->list.rowHeight;
        menu->list.slotIndex = slot;
        menu->column = column;
        RefreshScrollListLayout_020be138(&menu->list, func_ov039_020bc1bc());
        SlotMenu_ReloadVisibleSlots_020c7144(menu);
    }
    switch (mode) {
    case 1:
        xOffset = 0x7a;
        break;
    default:
        xOffset = 0;
        break;
    }
    base = 0x40;
    if (column != 2) {
        base = 0x30;
    }
    cursor->x = base + xOffset;
    base = 0x1c;
    if (column >= 2) {
        base = 0x18;
    }
    cursor->y = column * 16 + (base + (slot - menu->list.topSlot) * 0x40);
}
