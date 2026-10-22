#include "nitro/types.h"
#include "nitro/fx.h"

typedef float f32;
#include "src/overlays/ov041/StageEntryRender.h"

/* A whole count as fx32, rounded half away from zero (converted once, after the rounding). */
#define COUNT_TO_FX32(x) ((fx32)((x) > 0 ? (f32)((x) << FX32_SHIFT) + 0.5f : (f32)((x) << FX32_SHIFT) - 0.5f))

#define ENTRY_KIND_THRESHOLDS 0x17 /* the only kind whose hp thresholds count */

extern const StageHpThresholds gEntryHpThresholds;
extern fx32 FX_Div(fx32 numer, fx32 denom);

/*
 * After a hit, for the one entry kind that uses them: when its hp crossed one of the thresholds (fractions of its
 * maximum) since the last check and one of the first three secondary entries is out, it is forced to its second
 * action and the check point moves to its hp now.
 */
void CheckEntryHpThresholds(StageEntry *entry)
{
    StageWork *work = gMovieContextState->stageWork;
    fx32 hp;
    fx32 checkedHp;
    BOOL crossed;
    BOOL secondaryOut;
    StageHpThresholds thresholds;
    fx32 maxHp;
    int i;

    hp = COUNT_TO_FX32(entry->hp);
    maxHp = COUNT_TO_FX32(entry->maxHp);
    checkedHp = COUNT_TO_FX32(entry->checkedHp);
    if (entry->kind == ENTRY_KIND_THRESHOLDS) {
        crossed = FALSE;
        secondaryOut = FALSE;
        thresholds = gEntryHpThresholds;
        for (i = 0; i < 4; i++) {
            fx32 threshold = thresholds.values[i];

            if (FX_Div(hp, maxHp) <= threshold && threshold < FX_Div(checkedHp, maxHp)) {
                crossed = TRUE;
                break;
            }
        }
        if (crossed) {
            for (i = 0; i < 3; i++) {
                if ((work->entries + work->primaryCount)[i].state == STAGE_ENTRY_OUT) {
                    secondaryOut = TRUE;
                    break;
                }
            }
            if (secondaryOut) {
                entry->flags |= STAGE_ENTRY_FORCE_ACTION_2;
                entry->checkedHp = entry->hp;
            }
        }
    }
}
