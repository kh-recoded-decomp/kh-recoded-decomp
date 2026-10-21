#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetEntryState(StageEntry *entry, int state);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern void GetStageGridPosition(VecFx32 *position, u8 row, u8 column);
extern void StartStageEntryMotion(StageEntry *entry, const VecFx32 *start, const VecFx32 *end, fx32 duration,
                                  int profile);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern BOOL StepEntryMotion(StageEntry *entry, fx32 step);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);

static inline VecFx32 GroundPosition(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    return position;
}

static inline VecFx32 GridPosition(u8 row, u8 column)
{
    VecFx32 position;

    GetStageGridPosition(&position, row, column);
    return position;
}

static inline void SpawnAppearEffect(StageEntry *entry)
{
    VecFx32 position;

    GetPositionAboveGround(&position, entry);
    SpawnStageItem(entry, 0xff, 1, 0, &position, FALSE);
}

/*
 * Entry state 0 (entering): a player walks to its grid place over 30 frames; an enemy appears with an effect
 * (three frames apart, the first with a sound) when the intro value is 2 or more. Afterwards the entry waits,
 * or starts active when the intro kind says so (2 for players, 3 for enemies).
 */
void StageEntryStateEnter(u8 entryIndex)
{
    StageEntry *entry;
    StageWork *work = gMovieContextState->stageWork;

    entry = &work->entries[entryIndex];
    if (!(entry->flags & STAGE_ENTRY_ENEMY)) {
        switch (entry->stateStep) {
        case 0:
            if (entry->flags & 4) {
                SetEntryState(entry, STAGE_ENTRY_WAITING);
                return;
            }
            {
                VecFx32 start = GroundPosition(entry);
                VecFx32 end = GridPosition(entry->row, entry->column);

                StartStageEntryMotion(entry, &start, &end, 30 * FX32_ONE, STAGE_MOTION_STEADY);
            }
            SetSceneEntryAnimation(entry, entry->stepAnimation, 1, 0);
            entry->stateStep++;
        case 1:
            if (!StepEntryMotion(entry, work->frameStep)) {
                return;
            }
            SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
            switch (work->introKind) {
            case 1:
                break;
            case 2:
                SetEntryState(entry, STAGE_ENTRY_ACTIVE);
                return;
            case 3:
                break;
            }
            SetEntryState(entry, STAGE_ENTRY_WAITING);
            return;
        }
        return;
    }
    if (work->introValue >= 2) {
        switch (entry->stateStep) {
        case 0:
            if ((entry->index - work->primaryCount) * 3 + 2 > work->frameCounter) {
                return;
            }
            if (entry->index == work->primaryCount) {
                PlayStageSound(0x1a0, 4, TRUE);
            }
            SpawnAppearEffect(entry);
            entry->stateStep++;
        case 1:
            switch (work->introKind) {
            case 1:
            case 2:
                break;
            case 3:
                SetEntryState(entry, STAGE_ENTRY_ACTIVE);
                return;
            }
            SetEntryState(entry, STAGE_ENTRY_WAITING);
            return;
        }
        return;
    }
    switch (work->introKind) {
    case 1:
    case 2:
        break;
    case 3:
        SetEntryState(entry, STAGE_ENTRY_ACTIVE);
        return;
    }
    SetEntryState(entry, STAGE_ENTRY_WAITING);
}
