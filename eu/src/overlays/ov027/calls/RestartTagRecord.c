#include "nitro/types.h"

typedef struct TagRecord {
    u16 id;
    u16 tagCount;
    u16 frame;
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

extern u64 OS_GetTick(void);
extern void TagTracker_InvokeCallback(void *tracker, int tag);

void RestartTagRecord(void *tracker, TagRecord *record)
{
    int frame;
    int tag;
    u64 tick;

    frame = record->elapsed = 0;
    tick = OS_GetTick();
    record->lastTick = tick;
    tag = record->tags[frame];
    record->frame = frame;
    TagTracker_InvokeCallback(tracker, tag);
}
