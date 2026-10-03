#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2a];
    s16 linkedId;
    s32 trackedIndex;
} TrackedRecordEntry;

extern void InitRecordEntry_020d4500(TrackedRecordEntry *entry);

void InitTrackedRecordEntry_020d5ee8(TrackedRecordEntry *entry)
{
    InitRecordEntry_020d4500(entry);
    entry->linkedId = -1;
    entry->trackedIndex = -1;
}
