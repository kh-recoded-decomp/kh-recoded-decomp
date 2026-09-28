#include "nitro/types.h"

typedef struct {
    u8 overlaySet;
    u8 pad_001[0x12f];
    u16 unk_130;
    u8 pad_132[2];
    u8 unk_134;
} OverlaySelectionRecord;

typedef struct {
    u8 pad_00[0x20];
    s32 unk_20;
} SlotPair0Entry;

typedef struct {
    u8 pad_0000[0x2db6];
    u16 unk_2DB6;
} GameState;

extern GameState *data_0205fe0c;

extern OverlaySelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern SlotPair0Entry *GetRecordSlotPair0Entry_02051ec8(s32 index);

void SyncSelectionRecordFromSlotEntry_0204fabc(void)
{
    OverlaySelectionRecord *record = GetOverlaySelectionRecord_0204f768(0);
    u16 entryIndex = data_0205fe0c->unk_2DB6;

    OpenRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    record->unk_130 = GetRecordSlotPair0Entry_02051ec8(entryIndex)->unk_20;
    record->unk_134 = 0;
    ReleaseRecordSlot_02051dfc(0);
    CloseRecordManager_02051cdc();
}
