#include "nitro/types.h"

typedef struct ListEntry {
    u16 x;
    u16 y;
    u32 unk_4;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[8];
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
} ListData;

typedef struct SlotRecord {
    u8 pad_00[6];
    u16 entryIndex;
} SlotRecord;

typedef struct ListView {
    void (*onChange)(void);
    ListData *data;
    u8 pad_08[0x70 - 0x08];
    SlotRecord *slots[3];
    u8 pad_7c[0x98 - 0x7c];
    int targetX;
    BOOL scrolling;
    BOOL cancelled;
    int cursorIndex;
} ListView;

extern void func_ov073_020c303c(ListView *list, int count, SlotRecord **slots);
extern void PlaceCursorAtListEntry_020c3778(ListView *list, int entryIndex);
extern void SelectListEntry_020c3718(ListView *list, int entryIndex);

void RewindListToPreviousSlot_020c3e24(ListView *list)
{
    ListTable *table = list->data->table;
    SlotRecord *slots[3] = { NULL, NULL, NULL };
    int i;
    int row;
    int scroll;
    ListEntry *entries;

    if (list->cancelled) {
        return;
    }
    row = (table->entries[list->cursorIndex].y - 2) / 16;
    if (row <= 0) {
        return;
    }
    list->cursorIndex = list->slots[row - 1]->entryIndex;
    for (i = row - 1; i < 3; i++) {
        slots[i] = list->slots[i];
    }
    func_ov073_020c303c(list, row - 1, slots);
    PlaceCursorAtListEntry_020c3778(list, list->cursorIndex);
    SelectListEntry_020c3718(list, list->cursorIndex);
    entries = table->entries;
    entries += list->cursorIndex;
    scroll = -((entries->y - 2) * 8);
    if (scroll > 0) {
        scroll = 0;
    } else if (scroll < -0x100) {
        scroll = -0x100;
    }
    list->targetX = scroll;
    list->scrolling = TRUE;
    if (list->onChange != NULL) {
        list->onChange();
    }
}
