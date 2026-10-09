#include "nitro/types.h"

typedef struct StageEntry {
    u8 kind;
    u8 pad_001[0x4b3];
} StageEntry;

typedef struct StageWork {
    u8 pad_000[0x14];
    StageEntry *entries;
    u8 entryCount;
} StageWork;

typedef struct MovieContextState {
    u8 pad_000[0xb8];
    StageWork *stageWork;
} MovieContextState;

extern MovieContextState *gMovieContextState;

BOOL HasStageEntryKind(int kind)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    BOOL found;

    found = FALSE;
    i = 0;

    while (i < work->entryCount) {
        if (kind == work->entries[i].kind) {
            found = TRUE;
            break;
        }
        ++i;
    }
    return found;
}
