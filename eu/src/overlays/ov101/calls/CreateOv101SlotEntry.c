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
    u8 pad_0000[0x184];
    u8 slotLists[2][0x6434];
    SlotEntry primaryEntries[12];
    SlotEntry secondaryEntries[12];
} Ov101State;

extern int PXI_Init_0204f0c8(void *slotList, int resourceId, int resourceParam);
extern void func_0204f218(void *slotList, int recordIndex, int value);
extern void IndexedRecord_ClearActive(void *slotList, int recordIndex);
extern void func_0204f18c(void *slotList, int recordIndex, int scale);
extern void Slot_SetMode2Bit(void *slotList, int recordIndex, int value);
extern void IndexedRecords_SetFlag2(void *slotList, int recordIndex, int visible);
extern int IndexedRecord_SetActive(void *slotList, int recordIndex);
extern void func_ov101_020c00b8(int listIndex, int entryIndex, int x, int y, Ov101State *state);
extern s16 *GetOv101SlotEntryResource(int listIndex, int entryIndex, Ov101State *state);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void CreateOv101SlotEntry(int listIndex, int entryIndex, SlotEntryConfig *config, Ov101State *state)
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
    recordIndex = PXI_Init_0204f0c8(slotList, config->resourceId, config->resourceParam);
    func_0204f218(slotList, recordIndex, 0);
    IndexedRecord_ClearActive(slotList, recordIndex);
    func_0204f18c(slotList, recordIndex, 0);
    Slot_SetMode2Bit(slotList, recordIndex, 0);
    IndexedRecords_SetFlag2(slotList, recordIndex, config->visible);
    if (config->raised != 0) {
        IndexedRecord_SetActive(slotList, recordIndex);
    }
    entry->recordIndex = recordIndex;
    entry->x = config->x;
    entry->y = config->y;
    func_ov101_020c00b8(listIndex, entryIndex, config->x, config->y, state);
    rect = GetOv101SlotEntryResource(listIndex, entryIndex, state);
    entry->width = rect[0] - rect[2] + 1;
    entry->height = rect[1] - rect[3] + 1;
    MI_CpuCopy8(rect, entry->bounds, 8);
}
