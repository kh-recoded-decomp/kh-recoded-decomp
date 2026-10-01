#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) ((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct {
    u8 pad_00[2];
    u16 useCount;
} SharedRecord;

typedef struct {
    u8 pad_000[0x20];
    u8 renderObj[0x2c];
    void *renderUser;
    u8 pad_050[0xb4];
    u8 recordState[0x2c];
    s8 slot;
    s8 active;
    u8 pad_132[0x1a];
} SlotMarker;

extern void func_01ff8830(void *dest, u32 value, u32 size);
extern u32 func_ov001_0206dba0(u32 index);
extern SharedRecord *RetainOrInitializeSharedRecord_0202c80c(u32 key, u32 context);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed9c(SlotMarker *object, SharedRecord *record, void *block, u32 context);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void RegisterSbcCallback_020188a4(void *renderObj, void (*func)(void *rs), u8 *unused, u8 cmd, int timing);
extern void OverrideNodeTranslation_020ab638(void *rs);
extern void *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void AcquireSharedRecordState_020a9054(void *state, u32 key, u32 initArg, u32 context);

void InitSlotMarker_020ab6dc(SlotMarker *marker, u32 slot)
{
    SharedRecord *record;
    void *block = NULL;

    func_01ff8830(marker, 0, sizeof(SlotMarker));
    marker->slot = slot;
    *(u32 *)marker->recordState = 0;
    marker->active = 0;
    record = RetainOrInitializeSharedRecord_0202c80c(ARCHIVE_FILE_ID(func_ov001_0206dba0(2), 2), slot + 8);
    if (record->useCount == 0) {
        block = func_0202c48c(ARCHIVE_FILE_ID(func_ov001_0206dba0(2), 3), 0x11);
    }
    func_0202ed9c(marker, record, block, slot + 8);
    if (block != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(block);
    }
    marker->renderUser = marker;
    RegisterSbcCallback_020188a4(marker->renderObj, OverrideNodeTranslation_020ab638, NULL, 6, 3);
    GetOverlaySelectionRecord_0204f768(slot);
    AcquireSharedRecordState_020a9054(marker->recordState, ARCHIVE_FILE_ID(func_ov001_0206dba0(1), 0), (u32)marker, slot + 8);
}
