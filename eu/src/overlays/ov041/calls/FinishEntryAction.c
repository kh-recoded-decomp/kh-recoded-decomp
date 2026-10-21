#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void ClearEntryActionState(StageEntry *entry);
extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern void SetFieldSlotHudRecord(int slot, int kind, BOOL useKind);
extern void UpdateEntryStatusItem(u8 entryIndex);
extern void SetEntryState(StageEntry *entry, int state);

/*
 * Ends an entry's action: clears every entry's hp display, lifts its one-action status 0 for the kinds of action
 * that use it up (not on effects 0xb7/0xb8 nor for kinds 0xfd/0xfe), and puts it back to waiting.
 */
void FinishEntryAction(StageEntry *entry)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    BOOL keep;

    ClearEntryActionState(entry);
    entry->lastActor = entry->index;
    for (i = 0; i < work->entryCount; i++) {
        work->entries[i].flags &= ~STAGE_ENTRY_SHOW_HP;
        work->entries[i].flags &= ~0x1000000;
    }
    switch (GetEntryAction(entry)->kind) {
    case 12:
        keep = FALSE;
        switch (GetEntryAction(entry)->effect) {
        case 0xb7:
        case 0xb8:
            keep = TRUE;
            break;
        }
        if (keep) {
            break;
        }
    case 14:
    case 15:
    case 16:
        keep = FALSE;
        switch (entry->kind) {
        case 0xfd:
        case 0xfe:
            keep = TRUE;
            break;
        }
        if (keep) {
            break;
        }
    case 0:
    case 3:
    case 4:
    case 5:
    case 13:
        if (entry->statuses[0] == 1) {
            entry->statuses[0] = 0;
            SetFieldSlotHudRecord(entry->index, 7, FALSE);
        }
        break;
    }
    UpdateEntryStatusItem(entry->index);
    entry->actionIndex = -1;
    SetEntryState(entry, STAGE_ENTRY_WAITING);
}
