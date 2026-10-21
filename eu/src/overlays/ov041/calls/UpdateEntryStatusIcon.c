#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define STATUS_ICON_NONE 8

extern void SetFieldSlotHudRecord(int slot, int kind, BOOL useKind);

/*
 * Shows a player entry's status icons in its HUD slot, one at a time: every 30 frames the next icon of a status
 * it has takes over; with none, every icon is cleared.
 */
void UpdateEntryStatusIcon(StageEntry *entry)
{
    StageWork *work = gMovieContextState->stageWork;
    u32 icons;
    int count;

    if (entry->flags & STAGE_ENTRY_ENEMY) {
        return;
    }
    icons = 0;
    count = 0;
    if (entry->statuses[10] > 0) {
        count++;
        icons |= 1 << 6;
    }
    if (entry->statuses[2] > 0) {
        count++;
        icons |= 1 << 0;
    }
    if (entry->statuses[1] > 0) {
        count++;
        icons |= 1 << 1;
    }
    if (entry->statuses[4] > 0) {
        count++;
        icons |= 1 << 2;
    }
    if (entry->statuses[0] > 0) {
        count++;
        icons |= 1 << 7;
    }
    if (entry->statuses[3] > 0) {
        count++;
        icons |= 1 << 3;
    }
    if (entry->statuses[9] > 0) {
        count++;
        icons |= 1 << 5;
    }
    if (entry->statuses[7] > 0) {
        count++;
        icons |= 1 << 4;
    }
    if (work->frameCounter % 30 == 0) {
        if (count == 0) {
            SetFieldSlotHudRecord(entry->index, 6, FALSE);
            SetFieldSlotHudRecord(entry->index, 0, FALSE);
            SetFieldSlotHudRecord(entry->index, 1, FALSE);
            SetFieldSlotHudRecord(entry->index, 2, FALSE);
            SetFieldSlotHudRecord(entry->index, 7, FALSE);
            SetFieldSlotHudRecord(entry->index, 3, FALSE);
            SetFieldSlotHudRecord(entry->index, 5, FALSE);
            SetFieldSlotHudRecord(entry->index, 4, FALSE);
            entry->shownStatusIcon = STATUS_ICON_NONE;
            return;
        }
        do {
            entry->shownStatusIcon++;
            if (entry->shownStatusIcon >= STATUS_ICON_NONE) {
                entry->shownStatusIcon = 0;
            }
        } while (!(icons & (1 << entry->shownStatusIcon)));
    }
    if (count != 0 && entry->shownStatusIcon < STATUS_ICON_NONE) {
        SetFieldSlotHudRecord(entry->index, entry->shownStatusIcon, TRUE);
    }
}
