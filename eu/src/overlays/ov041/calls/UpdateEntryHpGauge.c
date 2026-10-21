#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern fx32 FX_Mul(fx32 a, fx32 b);
extern void ShowEntryHpGauge(StageEntry *entry);

/*
 * Shows an entry's hp gauge while it should be visible, and lets the shown hp drain toward the real one by a
 * twentieth of the maximum (at least 1) per frame.
 */
void UpdateEntryHpGauge(StageEntry *entry)
{
    BOOL show = FALSE;
    fx32 step;

    if ((entry->flags & STAGE_ENTRY_SHOW_HP) &&
        (entry->shownHp != 0 || entry->state != STAGE_ENTRY_OUT || entry->stateStep != 3)) {
        show = TRUE;
    }
    if (entry->state == 13 || entry->state == 14) {
        show = TRUE;
    }
    if (show) {
        ShowEntryHpGauge(entry);
    }
    if (entry->shownHp > entry->hp) {
        step = FX_Mul(entry->maxHp << FX32_SHIFT, 0xcd);
        if (step < FX32_ONE) {
            step = FX32_ONE;
        }
        entry->shownHp -= (s16)(step >> FX32_SHIFT);
        if (entry->shownHp < entry->hp) {
            entry->shownHp = entry->hp;
        }
    }
}
