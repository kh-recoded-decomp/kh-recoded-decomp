#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const StageSoundChoices gStageStatusSounds;
extern int GetCommandStatusIndex(int commandId);
extern int func_0202a9e4(u16 range);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void func_ov001_020786d0(int index);
extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void SetEntryState(StageEntry *entry, int state);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);

/*
 * Entry state for a status command: plays one of two sounds and the casting animation, puts the status
 * (GetCommandStatusIndex) on the command's targets for 6 turns (2 for status 0) with the status item over each,
 * clears status 6 from the caster (ticking the 16 field entries), then returns to waiting once the animation is
 * done.
 */
void EntryStateStatusCommand(u8 entryIndex)
{
    StageWork *work = gMovieContextState->stageWork;
    StageEntry *entry = &work->entries[entryIndex];
    u8 turns = 6; /* how long the status lasts */
    int i;
    StageSoundChoices sounds;

    if (GetCommandStatusIndex(work->commandId) == 0) {
        turns = 2;
    }
    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        i = func_0202a9e4(2000) / 1000;
        sounds = gStageStatusSounds;
        PlayStageSound(0x30, sounds.indices[i], TRUE);
        SetSceneEntryAnimation(entry, 10, 0, 1);
        i = 0;
        switch (work->commandEffectKind) {
        case 0:
        case 7:
        case 9:
            if (work->entries[work->targetIndex].state != STAGE_ENTRY_OUT) {
                VecFx32 position;

                GetPositionAboveGround(&position, &work->entries[work->targetIndex]);
                SpawnStageItem(entry, 0xff, 0x13, i, &position, i);
                if (GetCommandStatusIndex(work->commandId) >= 0 &&
                    GetCommandStatusIndex(work->commandId) < STAGE_ENTRY_STATUS_COUNT) {
                    work->entries[work->targetIndex].statuses[GetCommandStatusIndex(work->commandId)] = turns;
                }
            }
            break;
        case 8:
            for (i = 0; i < work->primaryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    VecFx32 position;

                    GetPositionAboveGround(&position, &work->entries[i]);
                    SpawnStageItem(entry, 0xff, 0x13, 0, &position, FALSE);
                    if (GetCommandStatusIndex(work->commandId) >= 0 &&
                        GetCommandStatusIndex(work->commandId) < STAGE_ENTRY_STATUS_COUNT) {
                        work->entries[i].statuses[GetCommandStatusIndex(work->commandId)] = turns;
                    }
                }
            }
            break;
        case 4:
            for (i = work->primaryCount; i < work->entryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    VecFx32 position;

                    GetPositionAboveGround(&position, &work->entries[work->targetIndex]);
                    SpawnStageItem(entry, 0xff, 0x13, 0, &position, FALSE);
                    if (GetCommandStatusIndex(work->commandId) >= 0 &&
                        GetCommandStatusIndex(work->commandId) < STAGE_ENTRY_STATUS_COUNT) {
                        work->entries[i].statuses[GetCommandStatusIndex(work->commandId)] = turns;
                    }
                }
            }
            break;
        }
        if (entry->statuses[6] > 0) {
            for (i = 0; i < 16; i++) {
                func_ov001_020786d0(i);
            }
            entry->statuses[6] = 0;
        }
        if (work->state == 0xf) {
            PlayStageSound(0x1a0, 0x22, TRUE);
        } else {
            PlayStageSound(0x1a0, 0xe, TRUE);
        }
        entry->stateStep++;
    case 2:
        if (!IsEntryFlag2Set(entry)) {
            SetEntryState(entry, 1);
        }
        break;
    }
    if (MatchesEitherSlotId(entry, 10) && !IsEntryFlag2Set(entry)) {
        SetSceneEntryAnimation(entry, entry->idleAnimation, 0, 0);
    }
}
