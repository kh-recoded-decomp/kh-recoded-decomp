#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x17C];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

extern void func_0204f2e4(void *recordBase, int recordIndex);
extern void func_0204f204(void *recordBase, int recordIndex, u16 frame);

void SetEntryAnimFrame_020bfcd0(int listIndex, int entryIndex, int frame, Ov101State *state)
{
    void *slotList = state->slotLists[listIndex];
    SlotEntry *entry;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }

    func_0204f2e4(slotList, entry->recordIndex);
    func_0204f204(slotList, entry->recordIndex, frame);
}
