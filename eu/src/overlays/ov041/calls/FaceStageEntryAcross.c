#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern const u8 data_ov041_020cf7a0[];

/*
 * Turns a waiting entry to face the other side, unless its facing is locked: enemies by the angle their kind
 * has in data_ov041_020cf7a0 (degrees off 90), players to 0xc004. Clears entry flag 4.
 */
void FaceStageEntryAcross(u8 entryIndex)
{
    StageEntry *entry = &gMovieContextState->stageWork->entries[entryIndex];
    int yaw;

    if (entry->state != STAGE_ENTRY_WAITING) {
        return;
    }
    if (entry->flags & STAGE_ENTRY_ENEMY) {
        yaw = (90 - data_ov041_020cf7a0[entry->kind]) * 0xb6;
        if (!(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
            entry->slot.node.yaw = yaw;
            entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
        }
    } else if (!(entry->slot.flags & STAGE_SLOT_FACING_LOCKED)) {
        entry->slot.node.yaw = 0xc004;
        entry->slot.node.flags |= STAGE_MODEL_USE_YAW;
    }
    entry->flags &= ~4;
}
