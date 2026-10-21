#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void SetSceneEntryAnimation(StageEntry *entry, int animation, int blend, int reset);
extern void GetPositionAboveGround(VecFx32 *position, StageEntry *entry);
extern StageResourceItem *SpawnStageItem(StageEntry *owner, int category, u8 index, u8 animation,
                                         const VecFx32 *position, BOOL persistent);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void SetEntryState(StageEntry *entry, int state);

/*
 * Entry state 14 (healed): plays the heal animation and effect, gives back a tenth of the maximum hp, waits for
 * the effect to end and goes back to waiting.
 */
void StageEntryStateHealed(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];
    VecFx32 position;

    switch (entry->stateStep) {
    case 0:
        entry->stateStep++;
    case 1:
        SetSceneEntryAnimation(entry, entry->healAnimation, 1, 0);
        GetPositionAboveGround(&position, entry);
        entry->effects[0] = SpawnStageItem(entry, 0xff, 0x13, 0, &position, FALSE);
        PlayStageSound(0x1a0, 14, TRUE);
        entry->hp += (s16)(FX_Mul(entry->maxHp << FX32_SHIFT, 0x19a) >> FX32_SHIFT);
        if (entry->hp > entry->maxHp) {
            entry->hp = entry->maxHp;
        }
        entry->stateStep++;
    case 2:
        if (entry->effects[0]->flags & STAGE_ITEM_IN_USE) {
            break;
        }
        entry->effects[0] = NULL;
        entry->stateStep++;
    case 3:
        SetEntryState(entry, STAGE_ENTRY_WAITING);
        break;
    }
}
