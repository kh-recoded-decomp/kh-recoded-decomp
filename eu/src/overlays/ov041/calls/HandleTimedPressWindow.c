#include "nitro/types.h"
#include "nitro/fx.h"
#include "src/overlays/ov041/StageEntryRender.h"

typedef float f32;

/* A whole frame count as fx32, rounded the way the converter of the original tools did. */
#define FRAME_TO_FX32(x) ((x) > 0 ? (fx32)((f32)((x) << FX32_SHIFT) + 0.5f) : (fx32)((f32)((x) << FX32_SHIFT) - 0.5f))

extern StageEntryAction *GetEntryAction(StageEntry *entry);
extern BOOL MatchesEitherSlotId(StageEntry *entry, int animation);
extern int GetEntryAnimationFrame(StageEntry *entry);
extern void ShowEntryPairPanel(StageEntry *a, StageEntry *b);
extern void CheckPairTimedPress(StageEntry *attacker, StageEntry *target);

/*
 * While an entry plays the given animation, handles the timed press against each target: the panel during the
 * action's press window before the hit frame, the press check in the four frames before that window (status 10
 * on either side moves two of those frames into the window).
 */
void HandleTimedPressWindow(StageEntry *entry, int animation, fx32 hitFrame)
{
    StageEntryAction *action;
    StageWork *work = gMovieContextState->stageWork;
    int frame;
    int i;
    StageEntry *target;
    fx32 window;
    fx32 early;
    fx32 start;

    action = GetEntryAction(entry);
    if ((entry->flags & STAGE_ENTRY_ENEMY) && (work->entries[entry->mainTarget].flags & 4)) {
        return;
    }
    if (!MatchesEitherSlotId(entry, animation)) {
        return;
    }
    frame = GetEntryAnimationFrame(entry);
    for (i = 0; i < entry->targetCount; i++) {
        target = &work->entries[entry->targets[i]];
        window = FRAME_TO_FX32(action->pressWindow);
        early = 4 * FX32_ONE;
        if (entry->statuses[STAGE_ENTRY_STATUS_10] > 0 || target->statuses[STAGE_ENTRY_STATUS_10] > 0) {
            window += 2 * FX32_ONE;
            early -= 2 * FX32_ONE;
        }
        start = hitFrame - window;
        if (start <= frame && frame < hitFrame) {
            ShowEntryPairPanel(entry, target);
        } else if (start - early <= frame && frame < start) {
            CheckPairTimedPress(entry, target);
        }
    }
}
