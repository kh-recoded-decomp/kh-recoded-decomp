#include "nitro/types.h"

typedef struct {
    u8 data[0x18];
} SlotTemplate;

typedef struct {
    u32 fileId;
    u32 count;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct {
    u8 pad_0000[0x24];
    u32 cellArchive;
    u8 pad_0028[4];
    u32 paletteArchive;
    u8 pad_0030[0x184 - 0x30];
    u8 slotLists[2][0x6434];
} Ov101State;

extern const SlotTemplate data_ov101_020c1b38[];
extern const SlotTemplate data_ov101_020c1d98[];
extern void InitObjManager(void *manager, ObjManagerConfig *config);
extern void PXI_Init_0204f020(void *manager, u32 fileId);
extern void CreateOv101SlotEntry(int listIndex, int entryIndex, const SlotTemplate *slotTemplate, Ov101State *state);
extern BOOL IsStateFlagSet(int setIndex, int bitIndex);
extern void SetOv101SlotEntryVisible(int listIndex, int entryIndex, int value, Ov101State *state);
extern void SetEntryAnimFrame(int listIndex, int entryIndex, int frame, Ov101State *state);

#define ARCHIVE_FILE_ID(archive, index) (((((archive) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (index))

void InitListSlots(Ov101State *state)
{
    ObjManagerConfig config;
    int i;
    int owned;
    int slot;
    int row;
    int highlighted;

    config.fileId = ARCHIVE_FILE_ID(state->cellArchive, 3);
    config.count = 1;
    config.unk_08 = 0;
    config.unk_0C = 0;
    InitObjManager(state->slotLists[0], &config);
    PXI_Init_0204f020(state->slotLists[0], ARCHIVE_FILE_ID(state->paletteArchive, 0));
    for (i = 0; i < 12; i++) {
        CreateOv101SlotEntry(0, i, &data_ov101_020c1b38[i], state);
    }
    row = 0;
    do {
        owned = IsStateFlagSet(1, row);
        highlighted = IsStateFlagSet(2, row) != 0;
        SetOv101SlotEntryVisible(0, row + 3, owned, state);
        SetEntryAnimFrame(0, row + 3, highlighted, state);
        row++;
    } while (row < 9);
    config.fileId = ARCHIVE_FILE_ID(state->cellArchive, 1);
    config.count = 2;
    config.unk_08 = 0;
    config.unk_0C = 0;
    InitObjManager(state->slotLists[1], &config);
    for (slot = 0; slot < 20; slot++) {
        CreateOv101SlotEntry(1, slot, &data_ov101_020c1d98[slot], state);
    }
}
