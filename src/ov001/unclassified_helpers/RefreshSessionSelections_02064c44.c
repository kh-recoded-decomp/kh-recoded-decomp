#include "nitro/types.h"

typedef struct {
    s32 values[3];
} SlotTriple;

typedef struct {
    u8 pad_00[6];
    s16 mode;
} SessionHeader;

typedef struct {
    SlotTriple slots[3];
    u16 ids[3];
    s16 mode;
    u8 pad_2c[4];
    s32 param;
    u8 pad_34[4];
    u8 extra[4];
} SessionSource;

typedef struct {
    u8 pad_0000[0x208];
    SessionHeader header;
    u8 pad_0210[0x10];
    SessionSource source;
    u8 pad_025c[0x274c - 0x25c - 4];
    SlotTriple slots[3];
    u16 ids[3];
    u8 pad_2772[0x27a8 - 0x2772];
    s32 counters[3];
    u8 pad_27b4[2];
    u8 dirty : 1;
    u8 pad_bits : 7;
    u8 pad_27b7[0x2938 - 0x27b7];
    s32 param;
} SessionState;

typedef struct {
    u16 pad_00;
    u16 current;
    u16 initial;
} SelectionRecord;

extern SessionState *data_ov001_020a0460;
extern void func_ov001_02062fa4(void *extra);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern void LoadDifficultyPresetIntoSession_020644d4(void);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern void SetupAllSelectionRecords_0204f85c(void);
extern void FillSelectionRecordFromGroup_0204f8dc(void);
extern void BuildSelectionEntryList_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);
extern void RebuildRecordCounters_02028e6c(void);
extern void func_02050a44(void);
extern SelectionRecord *func_0204f768(u32 index);

void RefreshSessionSelections_02064c44(void)
{
    int i;
    SessionState *state = data_ov001_020a0460;
    SessionHeader *header = &state->header;
    SessionSource *source = &state->source;

    func_ov001_02062fa4(source->extra);
    if (ReadSessionPackedBits_02064574(0x1a00, 2) != 3) {
        LoadDifficultyPresetIntoSession_020644d4();
    }
    i = 0;
    AcquireMapLayout_020506dc(1, 0);
    SetupAllSelectionRecords_0204f85c();
    FillSelectionRecordFromGroup_0204f8dc();
    BuildSelectionEntryList_0204f98c();
    SyncSelectionRecordFromSlotEntry_0204fabc();
    func_0204fba0();
    RebuildRecordCounters_02028e6c();
    func_02050a44();
    do {
        func_0204f768(i)->current = func_0204f768(i)->initial;
        state->counters[i] = 0;
        i++;
    } while (i < 3);
    i = 0;
    do {
        state->slots[i] = source->slots[i];
        state->ids[i] = source->ids[i];
        i++;
    } while (i < 3);
    header->mode = source->mode;
    state->param = source->param;
    state->dirty = 1;
}


