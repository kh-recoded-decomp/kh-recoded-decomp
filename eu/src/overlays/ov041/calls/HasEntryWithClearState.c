#include "nitro/types.h"

typedef struct {
    u8 pad_000[4];
    u8 state;
    u8 pad_005[3];
    u32 flags;
    u8 pad_00c[0x107];
    s8 locked;
    u8 pad_114[0x3a0];
} StageEntry;

typedef struct {
    u8 pad_00[0x14];
    StageEntry *entries;
    u8 entryCount;
} StageWork;

extern u8 *data_ov035_020bc4e0;

BOOL HasEntryWithClearState(BOOL wantClear) {
    int i;
    u32 result;
    StageWork *work;

    work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    result = FALSE;

    for (i = 0; i < work->entryCount; i++) {
        StageEntry *entry = &work->entries[i];
        if (entry->state != 6) {
            if ((wantClear && !(entry->flags & 1)) || (!wantClear && (entry->flags & 1))) {
                result = TRUE;
                break;
            }
        }
    }
    if (wantClear && work->entries->state == 6) {
        if (work->entries->locked == 0) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    }
    return result;
}
