#include "nitro/types.h"

typedef struct TagRecord {
    u16 id;
    u16 tagCount;
    vu16 frame;
    u8 pad_06[2];
    int playOnce;
    u64 frameTicks;
    u64 elapsed;
    u64 lastTick;
    u8 active : 1;
    u8 armed : 1;
    u8 pad_25[3];
    int target;
    int *tags;
} TagRecord;

typedef struct TagTracker {
    u8 pad_00[0x10];
    TagRecord *records;
    u8 pad_14[0x20];
    int count;
    u8 pad_38[4];
    void (*apply)(int tag);
    u8 pad_40[4];
    void (*setTarget)(int target);
    int (*getTarget)(void);
} TagTracker;

extern u64 OS_GetTick_02003fd4(void);
extern u64 func_02023d60(u64 value, u64 divisor);

void TickTagRecords_020b7aa0(TagTracker *tracker)
{
    int i;
    int saved = -1;
    int prev = 0x7FFFFFFF;
    BOOL swap;
    TagRecord *record;
    u64 now = OS_GetTick_02003fd4();

    swap = FALSE;
    for (i = 0; i < tracker->count; i++) {
        record = &tracker->records[i];

        if (record->armed == 0) {
            continue;
        }
        if (record->active == 0) {
            continue;
        }
        if (record->frame >= record->tagCount - 1 && record->playOnce == 1) {
            continue;
        }
        record->elapsed += now - record->lastTick;
        record->lastTick = now;
        if (record->elapsed <= record->frameTicks) {
            continue;
        }
        record->frame = record->frame + 1;
        if (record->frame >= record->tagCount) {
            if (record->playOnce == 1) {
                record->frame = record->tagCount - 1;
            } else {
                record->frame = (u32)record->frame % (u32)record->tagCount;
            }
        }
        if (tracker->getTarget != NULL) {
            saved = tracker->getTarget();
            swap = (tracker->setTarget != NULL && record->target != prev);
        }
        if (swap) {
            tracker->setTarget(record->target);
        }
        tracker->apply(record->tags[record->frame]);
        if (swap) {
            tracker->setTarget(saved);
        }
        record->elapsed = func_02023d60(record->elapsed, record->frameTicks);
    }
}
