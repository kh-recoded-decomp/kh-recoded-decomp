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

typedef struct Ov081State {
    u8 pad_00[0x62d8];
    u8 visibleIndices[110];
    u8 pad_6346[2];
    u8 *bitIndexTable;
    u8 unseen[110];
    s8 unseenIcons[9];
    u8 visibleCount;
    u8 shownCount;
    u8 unseenIconCount;
} Ov081State;

typedef struct Ov082State {
    ScrollList list;
} Ov082State;

typedef struct IconPos {
    int x;
    int y;
} IconPos;

extern Ov081State *func_ov081_020c5bd8(void);
extern void *func_ov039_020bc1cc(void);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern IconPos *func_ov027_020b91a8(void *container, void *widget);
extern EntryList *GetSlotEntry_020c5438(int slot);
extern void func_ov082_020bf08c(Ov082State *state, int row, u8 entry, u8 mode);
extern void func_0204f13c(void *container, int icon, IconPos *pos);
extern BOOL AreSlotEntriesAllSeen_020c5964(int slot);
extern void func_0204f204(void *container, int icon, u16 frame);
extern void func_0204f2e4(void *container, int icon);
extern void func_0204f378(void *container, int icon, BOOL visible);

void RefreshEntryRows_020bef08(Ov082State *state)
{
    Ov081State *source = func_ov081_020c5bd8();
    void *container = func_ov039_020bc1cc();
    IconPos *base = func_ov027_020b91a8(container, FindWidgetById_020b90a4(container, 3));
    IconPos pos;
    int row;
    int icon;
    int slot;
    int count;
    int iconCount;
    u8 entry;

    count = source->shownCount;
    for (row = 0, icon = 0; row < count; row++) {
        slot = row + state->list.topSlot;
        entry = source->visibleIndices[slot];
        func_ov082_020bf08c(state, row, entry, GetSlotEntry_020c5438(slot)->kind == 2 ? 0 : 2);
        if (source->unseen[slot]) {
            pos = *base;
            pos.y = pos.y + ((row * state->list.rowHeight) << 12);
            func_0204f13c(container, source->unseenIcons[icon], &pos);
            if (!AreSlotEntriesAllSeen_020c5964(slot)) {
                func_0204f204(container, source->unseenIcons[icon], 0);
            } else {
                func_0204f204(container, source->unseenIcons[icon], 1);
            }
            func_0204f2e4(container, source->unseenIcons[icon]);
            func_0204f378(container, source->unseenIcons[icon], TRUE);
            icon++;
        }
    }
    iconCount = source->unseenIconCount;
    for (; icon < iconCount; icon++) {
        func_0204f378(container, source->unseenIcons[icon], FALSE);
    }
}
