#include "nitro/types.h"

typedef struct ScrollList {
    s16 count;
    s16 slotIndex;
    s16 topSlot;
    u8 pad_06;
    u8 visibleCount;
    u8 rowHeight;
    u8 pad_09[0x1f];
} ScrollList;

typedef struct EntryList {
    u8 kind;
} EntryList;

typedef struct CursorPos {
    int x;
    int y;
} CursorPos;

extern u16 data_020604fc;
extern u16 data_02060500;

extern void *func_ov081_020c5bd8(void);
extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern EntryList *FX_Div_020c542c();
extern EntryList *GetSlotEntry_020c5438(int slot);
extern void RefreshScrollListLayout_020be138(ScrollList *list, void *container);
extern void func_ov027_020b91c8(void *container, void *widget, CursorPos *pos, int mode);
extern void MarkUnlockedListEntriesSeen_020c5880();

void StepEntryListCursor_020bf448(ScrollList *list)
{
    void *container;
    void *cursor;
    int step;
    int top;
    CursorPos pos;

    func_ov081_020c5bd8();
    container = func_ov039_020bc1cc();
    cursor = FindWidgetById_020b90a4(container, 0);
    if (data_020604fc & 0x60) {
        step = -1;
    } else {
        step = 1;
    }
    while (FX_Div_020c542c()->kind == 2) {
        list->slotIndex += (s16)step;
        if (step == -1) {
            if (list->slotIndex < 0) {
                if (data_02060500 & 0x40) {
                    int shown = list->count < list->visibleCount ? list->count : list->visibleCount;
                    list->slotIndex += list->count;
                    list->topSlot = list->count - (u16)shown;
                } else {
                    list->slotIndex = 0;
                    step = -step;
                }
            } else if (list->slotIndex < list->topSlot) {
                list->topSlot = list->slotIndex;
            }
        } else if (list->slotIndex >= list->count) {
            if (data_02060500 & 0x80) {
                list->slotIndex -= list->count;
                list->topSlot = 0;
            } else {
                list->slotIndex = list->count - 1;
                step = -step;
            }
        } else if (list->slotIndex >= list->topSlot + list->visibleCount) {
            top = list->slotIndex - list->visibleCount + 1;
            if (top < 0) {
                top = 0;
            }
            list->topSlot = top;
        }
    }
    if (list->topSlot != 0 && list->visibleCount - 1 != list->slotIndex - list->topSlot
        && GetSlotEntry_020c5438(list->topSlot - 1)->kind == 2) {
        list->topSlot--;
    } else {
        top = list->slotIndex - list->visibleCount + 1;
        if (list->topSlot < top) {
            list->topSlot = top;
        }
    }
    RefreshScrollListLayout_020be138(list, container);
    pos.x = 0x10000;
    pos.y = (list->rowHeight * (list->slotIndex - list->topSlot)) << 12;
    func_ov027_020b91c8(container, cursor, &pos, 3);
    MarkUnlockedListEntriesSeen_020c5880();
}
