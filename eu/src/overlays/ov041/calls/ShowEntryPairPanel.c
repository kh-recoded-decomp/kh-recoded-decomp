#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void UpdateTimedPressPanel(StageEntry *player, StageEntry *other, BOOL playerFirst);

/* Calls UpdateTimedPressPanel with the non-enemy of the two first (b when both are), if either is one. */
void ShowEntryPairPanel(StageEntry *a, StageEntry *b)
{
    BOOL aIsPlayer = TRUE;
    BOOL bIsPlayer;

    if (a->flags & STAGE_ENTRY_ENEMY) {
        aIsPlayer = FALSE;
    }
    bIsPlayer = TRUE;
    if (b->flags & STAGE_ENTRY_ENEMY) {
        bIsPlayer = FALSE;
    }
    if (aIsPlayer || bIsPlayer) {
        if (bIsPlayer) {
            UpdateTimedPressPanel(b, a, FALSE);
        } else if (aIsPlayer) {
            UpdateTimedPressPanel(a, b, TRUE);
        }
    }
}
