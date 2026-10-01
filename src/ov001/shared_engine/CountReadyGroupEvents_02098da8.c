#include "nitro/types.h"

typedef struct StageEventRecord {
    u8 pad_00[6];
    u16 lowFlags : 8;
    u16 isFlagged : 1;
    u16 highFlags : 7;
} StageEventRecord;

typedef struct StageGroup {
    u8 pad_00[0xa];
    u16 firstEvent;
    s16 lastEvent;
} StageGroup;

extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);

u16 CountReadyGroupEvents_02098da8(StageGroup *group, BOOL flaggedOnly)
{
    u16 count = 0;
    u16 event;

    for (event = group->firstEvent; event <= group->lastEvent; event++) {
        StageEventRecord *record = GetStageEventRecord_0209c0ec((u16)(event + 1));

        if (record != NULL && (!flaggedOnly || record->isFlagged)) {
            count++;
        }
    }
    return count;
}
