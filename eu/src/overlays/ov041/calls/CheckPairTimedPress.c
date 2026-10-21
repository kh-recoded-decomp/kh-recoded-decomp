#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void CheckTimedPress(StageEntry *entry, BOOL defending);

/* Checks the timed press of whichever of attacker and target the player controls (kind 0xff first). */
void CheckPairTimedPress(StageEntry *attacker, StageEntry *target)
{
    BOOL attackerIsPlayer = TRUE;
    BOOL targetIsPlayer;

    if (attacker->flags & STAGE_ENTRY_ENEMY) {
        attackerIsPlayer = FALSE;
    }
    targetIsPlayer = TRUE;
    if (target->flags & STAGE_ENTRY_ENEMY) {
        targetIsPlayer = FALSE;
    }
    if (attackerIsPlayer || targetIsPlayer) {
        if (attacker->kind == 0xff) {
            CheckTimedPress(attacker, FALSE);
        } else if (target->kind == 0xff) {
            CheckTimedPress(target, TRUE);
        } else if (attackerIsPlayer) {
            CheckTimedPress(attacker, FALSE);
        } else if (targetIsPlayer) {
            CheckTimedPress(target, TRUE);
        }
    }
}
