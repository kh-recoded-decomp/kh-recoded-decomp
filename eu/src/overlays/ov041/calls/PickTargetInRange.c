#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

/* What the search passed over: an entry in range that is out, or one too far away. */
#define TARGET_SEEN_OUT 1
#define TARGET_SEEN_FAR 2

extern int func_0202a9e4(u16 range);

/*
 * Picks a random entry on the other side that is still in the fight and at most range rows (beyond three)
 * away, starting at a random one and going round. A player entry that finds none tries again one row further;
 * an enemy keeps the last one it looked at.
 */
int PickTargetInRange(StageEntry *entry, int range)
{
    int seen;
    StageWork *work;
    int target;
    int count;
    int first;
    int distance;
    StageEntry *candidate;
    int i;
    int row;

    seen = 0;
    work = gMovieContextState->stageWork;
    if (entry->flags & STAGE_ENTRY_ENEMY) {
        target = func_0202a9e4(work->primaryCount * 100) / 100;
        count = work->primaryCount;
        first = 0;
    } else {
        first = work->primaryCount;
        target = (first * 100 + func_0202a9e4(work->secondaryCount * 100)) / 100;
        count = work->entryCount;
    }
    for (i = 0; i < count; i++) {
        candidate = &work->entries[target];
        row = entry->row - candidate->row;
        if (row < 0) {
            row = -row;
        }
        distance = row - 3;
        if (candidate->state != STAGE_ENTRY_OUT && distance <= range) {
            seen = 0;
            break;
        }
        if (distance <= range) {
            seen |= TARGET_SEEN_OUT;
        } else {
            seen |= TARGET_SEEN_FAR;
        }
        target++;
        if (target >= count) {
            target = first;
        }
    }
    if (seen & (TARGET_SEEN_OUT | TARGET_SEEN_FAR)) {
        if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
            return PickTargetInRange(entry, range + 1);
        }
    } else if (seen & TARGET_SEEN_OUT) { /* never: seen is 0 here */
        target = entry->index;
    }
    return target;
}
