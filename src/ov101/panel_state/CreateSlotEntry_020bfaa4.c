#include "nitro/types.h"

typedef struct {
    s32 recordIndex;
    s32 x;
    s32 y;
    s32 width;
    s32 height;
    s16 bounds[4];
} SlotEntry;

typedef struct {
    s32 resourceId;
    s32 resourceParam;
    s32 x;
    s32 y;
    s32 visible;
    s32 raised;
} SlotEntryConfig;

typedef struct {
    u8 pad_0000[0x17C];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

extern int PXI_Init_0204f0b4(void *slotList, int resourceId, int resourceParam);
extern void func_0204f204(void *slotList, int recordIndex, int value);
extern void func_0204f2e4(void *slotList, int recordIndex);
extern void func_0204f178(void *slotList, int recordIndex, int scale);
extern void Slot_SetMode2Bit_0204f480(void *slotList, int recordIndex, int value);
extern void func_0204f378(void *slotList, int recordIndex, int visible);
extern int func_0204f2c0(void *slotList, int recordIndex);
extern void SetSlotEntryPosition_020bfbc4(int listIndex, int entryIndex, int x, int y, Ov101State *state);
extern s16 *GetSlotEntryResource_020bfd24(int listIndex, int entryIndex, Ov101State *state);
extern void func_01ff89a8(const void *src, void *dst, u32 size);

void CreateSlotEntry_020bfaa4(int listIndex, int entryIndex, SlotEntryConfig *config, Ov101State *state)
{
    void *slotList = state->slotLists[listIndex];
    SlotEntry *entry;
    int recordIndex;
    s16 *rect;

    if (listIndex == 0) {
        entry = &state->primaryEntries[entryIndex];
    } else {
        entry = &state->secondaryEntries[entryIndex];
    }
    recordIndex = PXI_Init_0204f0b4(slotList, config->resourceId, config->resourceParam);
    func_0204f204(slotList, recordIndex, 0);
    func_0204f2e4(slotList, recordIndex);
    func_0204f178(slotList, recordIndex, 0);
    Slot_SetMode2Bit_0204f480(slotList, recordIndex, 0);
    func_0204f378(slotList, recordIndex, config->visible);
    if (config->raised != 0) {
        func_0204f2c0(slotList, recordIndex);
    }
    entry->recordIndex = recordIndex;
    entry->x = config->x;
    entry->y = config->y;
    SetSlotEntryPosition_020bfbc4(listIndex, entryIndex, config->x, config->y, state);
    rect = GetSlotEntryResource_020bfd24(listIndex, entryIndex, state);
    entry->width = rect[0] - rect[2] + 1;
    entry->height = rect[1] - rect[3] + 1;
    func_01ff89a8(rect, entry->bounds, 8);
}
