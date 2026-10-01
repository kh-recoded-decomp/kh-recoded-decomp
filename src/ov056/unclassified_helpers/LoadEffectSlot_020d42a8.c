#include "nitro/types.h"

#define ARCHIVE_FILE_ID(archive, index) \
    (((((u32)(archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000) | ((index) & 0x1ff))

typedef struct {
    u32 initialized;
    void *record;
    u8 state[0x24];
} SharedRecordState;

typedef struct {
    u8 pad_000[0x104];
    SharedRecordState sharedState;
    BOOL isActive;
} EffectSlot;

typedef struct {
    u8 pad_00[0x10];
    s32 isLoaded;
} SharedRecord;

typedef struct {
    u8 pad_00[8];
    u8 loadContext[4];
} SlotLoadParams;

extern u32 func_ov001_0206dba0(u32 index);
extern SharedRecord *RetainOrInitializeSharedRecord_0202c80c(u32 fileId, void *context);
extern void *func_0202c48c(u32 fileId, u32 flags);
extern void func_0202ed9c(EffectSlot *slot, SharedRecord *record, void *data, void *context);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void AcquireSharedRecordState_020a9054(SharedRecordState *state, u32 fileId, EffectSlot *slot, void *context);

void LoadEffectSlot_020d42a8(EffectSlot *slot, u32 fileIndex, SlotLoadParams *params)
{
    void *context = params->loadContext;
    SharedRecord *record;
    void *data;

    slot->isActive = FALSE;
    record = RetainOrInitializeSharedRecord_0202c80c(ARCHIVE_FILE_ID(func_ov001_0206dba0(0), fileIndex), context);
    if (record->isLoaded != 0) {
        func_0202ed9c(slot, record, NULL, context);
    } else {
        data = func_0202c48c(ARCHIVE_FILE_ID(func_ov001_0206dba0(0), fileIndex + 2), 0x11);
        func_0202ed9c(slot, record, data, context);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(data);
    }
    slot->sharedState.initialized = 0;
    AcquireSharedRecordState_020a9054(&slot->sharedState, ARCHIVE_FILE_ID(func_ov001_0206dba0(0), fileIndex + 1), slot, context);
}
