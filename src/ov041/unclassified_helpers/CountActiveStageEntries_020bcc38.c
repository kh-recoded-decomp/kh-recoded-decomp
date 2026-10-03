#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u8 state;
    u8 pad_005[0x4af];
} StageEntry;

typedef struct {
    u8 pad_00[0x14];
    StageEntry *entries;
    u8 entryCount;
    u8 primaryCount;
    u8 secondaryCount;
} StageWork;

extern u8 *data_ov035_020bc4e0;

u8 CountActiveStageEntries_020bcc38(BOOL primary) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    u8 count = 0;
    int i;

    if (primary) {
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state != 6) {
                count++;
            }
        }
    } else {
        for (i = 0; i < work->secondaryCount; i++) {
            if ((work->entries + work->primaryCount)[i].state != 6) {
                count++;
            }
        }
    }
    return count;
}
