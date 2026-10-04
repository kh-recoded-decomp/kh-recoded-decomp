#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    u8 pad_0C[0x10];
} SlotEntry;

typedef struct {
    u8 pad_0000[0x17C];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

typedef struct {
    fx32 x;
    fx32 y;
} FxPoint;

extern void func_0204f13c(void *recordBase, int recordIndex, FxPoint *position);

void SetSlotEntryPosition_020bfbc4(int listIndex, int entryIndex, int x, int y, Ov101State *state)
{
    void *slotList = state->slotLists[listIndex];
    SlotEntry *entry;
    FxPoint position;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }

    entry->x = x;
    entry->y = y;
    position.x = (fx32)(((f32)entry->x > 0) ? ((f32)entry->x * 4096.0f + 0.5f) : ((f32)entry->x * 4096.0f - 0.5f));
    position.y = (fx32)(((f32)entry->y > 0) ? ((f32)entry->y * 4096.0f + 0.5f) : ((f32)entry->y * 4096.0f - 0.5f));
    func_0204f13c(slotList, entry->recordIndex, &position);
}
