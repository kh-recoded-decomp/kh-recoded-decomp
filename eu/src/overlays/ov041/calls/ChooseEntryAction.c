#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

typedef float f32;

extern int PickEntryActionInRange(StageEntry *entry);
extern u32 func_0202a9e4(u32 range);
extern void EntryActionHookNoop(int entryIndex, int actionKind);

/*
 * Picks the action an entry carries out next (PickEntryActionInRange). Kind 0x17 takes action 2 once when told
 * to; an enemy of kind 0xfd takes action 1 by that action's chance.
 */
void ChooseEntryAction(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entries = work->entries;
    StageEntry *entry = &entries[entryIndex];
    f32 hp = entry->hp;
    f32 maxHp = entry->maxHp;
    f32 unk = entry->unk0e2;

    entry->actionIndex = PickEntryActionInRange(entry);
    switch (entries[entryIndex].kind) {
    case 0x17:
        if (entry->flags & STAGE_ENTRY_FORCE_ACTION_2) {
            entry->actionIndex = 2;
            entry->flags &= ~STAGE_ENTRY_FORCE_ACTION_2;
        }
        break;
    case 0xfd:
        if (entry->flags & STAGE_ENTRY_ENEMY) {
            if (func_0202a9e4(1000) < entry->actions[1].chance) {
                entry->actionIndex = 1;
            }
        }
        break;
    }
    EntryActionHookNoop(entryIndex, entry->actions[entry->actionIndex].kind);
}
