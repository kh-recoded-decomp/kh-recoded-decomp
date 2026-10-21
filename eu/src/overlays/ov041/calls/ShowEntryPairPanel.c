#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern void func_ov041_020c4494(StageEntry *player, StageEntry *other, BOOL playerFirst);

/* Calls func_ov041_020c4494 with the non-enemy of the two first (b when both are), if either is one. */
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
            func_ov041_020c4494(b, a, FALSE);
        } else if (aIsPlayer) {
            func_ov041_020c4494(a, b, TRUE);
        }
    }
}
