#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_Y 0x0800

extern u16 data_02060500;

/* Marks an entry's timed press: A when it attacks, Y when it defends (unless status 9 stops it). */
void CheckTimedPress(StageEntry *entry, BOOL defending)
{
    BOOL pressed = FALSE;

    if (gMovieContextState->stageWork->flags & STAGE_WORK_NO_TIMED_INPUT) {
        return;
    }
    if (entry->flags & STAGE_ENTRY_TIMED_PRESS) {
        return;
    }
    if (defending && entry->statuses[STAGE_ENTRY_STATUS_9] > 0) {
        return;
    }
    if (defending) {
        if (data_02060500 & PAD_BUTTON_Y) {
            pressed = TRUE;
        }
    } else if (data_02060500 & PAD_BUTTON_A) {
        pressed = TRUE;
    }
    if (pressed) {
        entry->flags |= STAGE_ENTRY_TIMED_PRESS;
    }
}
