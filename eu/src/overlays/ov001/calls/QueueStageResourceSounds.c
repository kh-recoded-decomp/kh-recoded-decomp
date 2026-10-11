#include "nitro/types.h"
#pragma opt_propagation off

typedef struct StageSoundRecord {
    u8 reserved00[0x14];
    u32 soundArchiveA;
    u32 parameter18;
    u32 soundArchiveB;
} StageSoundRecord;

typedef struct StageSoundTable {
    u32 parameter00;
    u32 count;
    u32 stride;
    u8 *items;
} StageSoundTable;

typedef struct StageResource {
    u32 reserved[2];
    StageSoundTable *table;
} StageResource;

typedef struct StageResourceEntry {
    u32 parameter00;
    StageResource *resource;
} StageResourceEntry;

typedef struct StageSoundManager {
    u32 reserved00[2];
    StageResourceEntry entries[64];
    u8 reserved208[0x18dec - 0x208];
    u16 resourceCount;
} StageSoundManager;

extern StageSoundManager *gStageManager;
extern BOOL func_ov001_02063a24(void);
extern BOOL IsSessionFlagSet(u32 flag);
extern void QueueSoundCommandForArc(u32 archive);

static inline u32 GetSoundCount(StageResourceEntry *entry)
{
    StageResource *resource;
    if (entry == NULL) {
        return 0;
    }
    resource = entry->resource;
    if (resource == NULL) {
        return 0;
    }
    return resource->table->count;
}

static inline StageSoundRecord *GetSoundRecord(u32 index, StageResourceEntry *entry)
{
    int count;
    StageResource *resource;
    u8 *items;
    if (entry == NULL) {
        return NULL;
    }
    resource = entry->resource;
    if (resource == NULL) {
        return NULL;
    }
    count = GetSoundCount(entry);
    /* Fetch the payload after checking the entry count. */
    resource = entry->resource;
    items = resource->table->items;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (StageSoundRecord *)(items + index * resource->table->stride);
}

void QueueStageResourceSounds(void)
{
    int i;
    StageSoundRecord *record;
    int count;
    if (func_ov001_02063a24() && IsSessionFlagSet(0x360c)) {
        return;
    }
    i = 0;
    count = gStageManager->resourceCount;
    if (count > 0) {
      do {
        record = GetSoundRecord(0, &gStageManager->entries[i]);
        if (record != NULL) {
            if (record->soundArchiveA != 0) {
                QueueSoundCommandForArc(record->soundArchiveA);
            }
            if (record->soundArchiveB != 0) {
                QueueSoundCommandForArc(record->soundArchiveB);
            }
        }
        i++;
      } while (i < gStageManager->resourceCount);
    }
}
