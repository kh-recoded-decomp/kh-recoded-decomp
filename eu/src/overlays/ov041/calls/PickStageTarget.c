#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const StageTargetCandidates gEmptyTargetCandidates;
extern const StageColumnCandidates gEmptyColumnCandidates;
extern u32 func_0202a9e4(u16 range);
extern StageEntry *FindStageEntryBySceneSlot(int sceneSlot);

/*
 * Picks the entry an attack goes for. Mode 0: the secondary entry with the most hp (a random one of those tied).
 * Mode 1: the front entry still in the fight of the column with the most entries left (scene slots 3-11 are
 * laid out in rows of three; ties at random). -1 if none.
 */
int PickStageTarget(int mode)
{
    StageWork *work = gMovieContextState->stageWork;
    int result = -1;

    switch (mode) {
    case 0: {
        int best = 0;
        StageTargetCandidates candidates = gEmptyTargetCandidates;
        int i;
        int ties = 0;
        StageEntry *entry;

        for (i = work->primaryCount; i < work->entryCount; i++) {
            entry = &work->entries[i];
            if (entry->state == STAGE_ENTRY_OUT) {
                continue;
            }
            if (entry->hp > best) {
                best = entry->hp;
                ties = 0;
                candidates.indices[0] = i;
            } else if (best == entry->hp) {
                ties++;
                candidates.indices[ties] = i;
            }
        }
        if (ties > 0) {
            result = candidates.indices[(int)func_0202a9e4((ties + 1) * 1000) / 1000];
        } else {
            result = candidates.indices[0];
        }
        break;
    }
    case 1: {
        int best = -1;
        StageColumnCandidates columns = gEmptyColumnCandidates;
        int ties = 0;
        int slot;
        int count = 0;
        int column;

        for (column = 0; column < 3; column++) {
            for (slot = column + 3; slot < 12; slot += 3) {
                if (FindStageEntryBySceneSlot(slot) != NULL && FindStageEntryBySceneSlot(slot)->state != STAGE_ENTRY_OUT) {
                    count++;
                }
            }
            if (best < count) {
                best = count;
                ties = 0;
                columns.columns[0] = column;
            } else if (best == count) {
                ties++;
                columns.columns[ties] = column;
            }
            count = 0;
        }
        if (ties > 0) {
            column = columns.columns[(int)func_0202a9e4((ties + 1) * 1000) / 1000];
        } else {
            column = columns.columns[0];
        }
        for (slot = 0; slot < 12; slot += 3) {
            if (FindStageEntryBySceneSlot(column + 3 + slot) != NULL &&
                FindStageEntryBySceneSlot(column + 3 + slot)->state != STAGE_ENTRY_OUT) {
                result = FindStageEntryBySceneSlot(column + 3 + slot)->index;
                break;
            }
        }
        break;
    }
    }
    return result;
}
