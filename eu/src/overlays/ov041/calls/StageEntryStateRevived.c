#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern u32 IsEntryFlag2Set(StageEntry *entry);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void SetEntryState(StageEntry *entry, int state);

/*
 * Entry state handler for a revive: once its animation has played out, shows the heal effect and gives back
 * three tenths of the maximum hp; after 15 more frames goes back to idle, clears status 3, faces the other side
 * (unless locked) and waits.
 */
void StageEntryStateRevived(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];
    VecFx32 position;

    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        if (IsEntryFlag2Set(entry)) {
            break;
        }
        GetPositionAboveGround(&position, entry);
        SpawnStageItem(entry, 0xff, 0x13, 0, &position, FALSE);
        PlayStageSound(0x1a0, 14, TRUE);
        entry->hp = FX_Mul(entry->maxHp << FX32_SHIFT, 0x4cd) >> FX32_SHIFT;
        entry->shownHp = entry->hp;
        entry->stateStep++;
    case 2:
        if (data_ov041_020cff48.reviveWait < 15) {
            data_ov041_020cff48.reviveWait++;
            return;
        }
        data_ov041_020cff48.reviveWait = 0;
        SetSceneEntryAnimation(entry, entry->idleAnimation, 1, 0);
        entry->stateStep++;
    case 3:
        entry->statuses[STAGE_ENTRY_STATUS_3] = 0;
        if (!(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
            entry->slot.node.yaw = 0xc004;
            entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
        }
        SetEntryState(entry, STAGE_ENTRY_WAITING);
        break;
    }
}
