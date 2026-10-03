#include "nitro/types.h"

typedef struct TagRecordFlags {
    u8 armed : 1;
    u8 loaded : 1;
} TagRecordFlags;

typedef struct TagRecord {
    u8 pad_00[4];
    u16 frame;
    u8 pad_06[0xE];
    s64 elapsed;
    s64 startTick;
    TagRecordFlags flags;
    u8 pad_25[7];
    int *tags;
} TagRecord;

extern s64 OS_GetTick_02003fd4(void);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, int tag);

void SetTagRecordArmed_020b83e8(void *tracker, TagRecord *record, BOOL arm)
{
    char armed = 0;

    if (arm != 0) {
        armed = 1;
        if (record->flags.armed != 1) {
            record->elapsed = 0;
            record->startTick = OS_GetTick_02003fd4();
            TagTracker_InvokeCallback_020b8210(tracker, record->tags[record->frame]);
        }
    }
    record->flags.armed = armed;
}



