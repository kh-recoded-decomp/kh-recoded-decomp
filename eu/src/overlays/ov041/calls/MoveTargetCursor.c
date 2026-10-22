#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define PAD_KEY_RIGHT 0x0010
#define PAD_KEY_LEFT 0x0020
#define PAD_KEY_UP 0x0040
#define PAD_KEY_DOWN 0x0080
#define PAD_BUTTON_L 0x0200

extern u16 data_020604fc; /* buttons held */
extern u16 data_02060500; /* buttons pressed this frame */

extern StageEntry *FindStageEntryBySceneSlot(int sceneSlot);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void ReleaseCommandMarkers(void);
extern u8 CountActiveStageEntries(BOOL primary);
extern StageMarker *ShowStageMarker(int listIndex, const VecFx32 *position, BOOL persistent);
extern void UpdateMarkerScreenPosition(StageMarker *marker, const VecFx32 *world);
extern BOOL func_ov001_02077e68(void);
extern BOOL func_ov001_02077ef4(void);
extern s32 func_ov001_02078494(void);
extern void SetFieldMenuMode_02078360(int mode, int arg);

/* Whether a scene slot holds an entry still in the fight. */
#define SLOT_IN_FIGHT(slot)                                                                                          \
    (FindStageEntryBySceneSlot(slot) != NULL && FindStageEntryBySceneSlot(slot)->state != STAGE_ENTRY_OUT)

/* The position of the object an entry's slot holds (the object starts at the slot's flags). */
static inline VecFx32 *SlotObjectPosition(u32 *object)
{
    return (VecFx32 *)((u8 *)object + 0xa8);
}

/*
 * Moves the target cursor (StageWork.targetSlot) with the d-pad for the target kind of the chosen item (source 0) or
 * command (source 1), skipping slots with no entry in the fight, and plays the cursor sound when it moved. Then puts
 * the target markers up: on every entry the action reaches for the column and all-entry kinds (blinking: only on even
 * frames), else one on the cursor's entry.
 */
void MoveTargetCursor(int source)
{
    StageWork *work = gMovieContextState->stageWork;
    int kind;
    BOOL single = FALSE;
    int count;
    u8 previousSlot = work->targetSlot;
    int i;
    int markers;
    int startSlot = previousSlot; /* the cursor sound plays when the slot changed */

    switch (source) {
    case 0:
        kind = work->itemActions[0].targetKind;
        break;
    case 1:
        kind = work->commandEffectKind;
        break;
    }
    switch (kind) {
    case STAGE_TARGET_ONE: /* up and down change the column, left and right the row */
        if (data_02060500 & PAD_KEY_UP) {
            do {
                if (work->targetSlot % 3 == 0) {
                    work->targetSlot += 2;
                } else {
                    work->targetSlot -= 1;
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        } else if (data_02060500 & PAD_KEY_DOWN) {
            do {
                if (work->targetSlot % 3 == 2) {
                    work->targetSlot -= 2;
                } else {
                    work->targetSlot += 1;
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        } else if (data_02060500 & PAD_KEY_LEFT) {
            /* the next row back, after the last one the first */
            int column = previousSlot % 3;

            do {
                if (work->targetSlot / 3 == 3) {
                    work->targetSlot -= 6;
                } else {
                    work->targetSlot += 3;
                }
                if (!SLOT_IN_FIGHT(work->targetSlot)) {
                    /* nobody there: look along the new row, from the column the cursor came from (or remembers) */
                    int slot;
                    int start;

                    if (column == 0) {
                        start = work->targetSlot / 3 * 3;
                        for (slot = start; slot < start + 3; slot++) {
                            if (slot / 3 != start / 3) {
                                slot -= 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    } else if (column == 2) {
                        start = work->targetSlot / 3 * 3 + 2;
                        for (slot = start; slot > start - 3; slot--) {
                            if (slot / 3 != start / 3) {
                                slot += 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    } else {
                        start = work->targetColumn + work->targetSlot / 3 * 3;
                        for (slot = start; slot < start + 3; slot++) {
                            if (slot / 3 != start / 3) {
                                slot -= 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    }
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
            if (column != 1) {
                work->targetColumn = column;
            }
        } else if (data_02060500 & PAD_KEY_RIGHT) {
            /* the next row forward, before the first one the last */
            int column = previousSlot % 3;

            do {
                if (work->targetSlot / 3 == 1) {
                    work->targetSlot += 6;
                } else {
                    work->targetSlot -= 3;
                }
                if (!SLOT_IN_FIGHT(work->targetSlot)) {
                    /* nobody there: look along the new row, from the column the cursor came from (or remembers) */
                    int slot;
                    int start;

                    if (column == 0) {
                        start = work->targetSlot / 3 * 3;
                        for (slot = start; slot < start + 3; slot++) {
                            if (slot / 3 != start / 3) {
                                slot -= 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    } else if (column == 2) {
                        start = work->targetSlot / 3 * 3 + 2;
                        for (slot = start; slot > start - 3; slot--) {
                            if (slot / 3 != start / 3) {
                                slot += 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    } else {
                        start = work->targetColumn + work->targetSlot / 3 * 3;
                        for (slot = start; slot < start + 3; slot++) {
                            if (slot / 3 != start / 3) {
                                slot -= 3;
                            }
                            if (SLOT_IN_FIGHT(slot)) {
                                work->targetSlot = slot;
                                break;
                            }
                        }
                    }
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
            if (column != 1) {
                work->targetColumn = column;
            }
        }
        break;
    case STAGE_TARGET_COLUMN:
        /* up and down both go to the next row of the same column */
        if (data_02060500 & PAD_KEY_UP) {
            do {
                for (i = 0; i < 3; i++) {
                    work->targetSlot += 3;
                    if (work->targetSlot >= 12) {
                        work->targetSlot -= 9;
                    }
                    if (SLOT_IN_FIGHT(work->targetSlot)) {
                        break;
                    }
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        } else if (data_02060500 & PAD_KEY_DOWN) {
            do {
                for (i = 0; i < 3; i++) {
                    work->targetSlot += 3;
                    if (work->targetSlot >= 12) {
                        work->targetSlot -= 9;
                    }
                    if (SLOT_IN_FIGHT(work->targetSlot)) {
                        break;
                    }
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        }
        break;
    case STAGE_TARGET_ONE_PRIMARY: /* up and down along the primary row */
        if (data_02060500 & PAD_KEY_UP) {
            do {
                if (work->targetSlot % 3 == 0) {
                    work->targetSlot += 2;
                } else {
                    work->targetSlot -= 1;
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        } else if (data_02060500 & PAD_KEY_DOWN) {
            do {
                if (work->targetSlot % 3 == 2) {
                    work->targetSlot -= 2;
                } else {
                    work->targetSlot += 1;
                }
            } while (!SLOT_IN_FIGHT(work->targetSlot));
        }
        break;
    case 2:
    case 3:
    case STAGE_TARGET_ALL:
    case 5:
    case 6:
    case STAGE_TARGET_ALL_PRIMARY:
    case 9:
        break; /* no cursor to move */
    case STAGE_TARGET_FIELD_MENU:
        if (data_02060500 & PAD_BUTTON_L) {
            work->stateTimer = 1;
        } else if (data_020604fc & PAD_BUTTON_L) {
            if (data_02060500 & PAD_KEY_DOWN) {
                func_ov001_02077ef4();
                work->stateTimer = 2;
            } else if (data_02060500 & PAD_KEY_UP) {
                func_ov001_02077e68();
                work->stateTimer = 2;
            } else if (func_ov001_02078494() == 0 && (data_02060500 & PAD_KEY_RIGHT)) {
                SetFieldMenuMode_02078360(1, 1);
                work->stateTimer = 2;
            } else if (func_ov001_02078494() == 1 && (data_02060500 & PAD_KEY_LEFT)) {
                SetFieldMenuMode_02078360(0, 1);
                work->stateTimer = 2;
            }
        } else if (work->stateTimer == 1) {
            work->stateTimer = 0;
            func_ov001_02077ef4();
        }
        break;
    }
    if (work->targetSlot != startSlot) {
        PlayStageSound(0, 0, FALSE);
    }
    ReleaseCommandMarkers();
    switch (kind) {
    case STAGE_TARGET_ALL:
        count = 0;
        if (CountActiveStageEntries(FALSE) > 1) {
            if (!(work->frameCounter & 1)) {
                for (i = 0; i < work->entryCount; i++) {
                    StageEntry *entry = &work->entries[i];

                    if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->state != STAGE_ENTRY_OUT) {
                        VecFx32 position = entry->slot.node.position;

                        work->commandMarkers[count++] = ShowStageMarker(3, &position, TRUE);
                    }
                }
            }
        } else {
            single = TRUE;
        }
        break;
    case STAGE_TARGET_ALL_PRIMARY:
        if (CountActiveStageEntries(TRUE) > 1) {
            if (!(work->frameCounter & 1)) {
                count = 0;
                for (i = 0; i < work->entryCount; i++) {
                    StageEntry *entry = &work->entries[i];

                    if (!(entry->flags & STAGE_ENTRY_ENEMY) && entry->state != STAGE_ENTRY_OUT) {
                        VecFx32 position = entry->slot.node.position;

                        work->commandMarkers[count++] = ShowStageMarker(3, &position, TRUE);
                    }
                }
            }
        } else {
            single = TRUE;
        }
        break;
    case STAGE_TARGET_COLUMN:
        count = 0;
        for (i = 0; i < work->entryCount; i++) {
            if ((work->entries[i].flags & STAGE_ENTRY_ENEMY) && work->entries[i].state != STAGE_ENTRY_OUT &&
                work->entries[i].column ==
                    work->entries[FindStageEntryBySceneSlot(work->targetSlot)->index].column) {
                count++;
            }
        }
        if (count > 1) {
            if (!(work->frameCounter & 1)) {
                markers = 0;
                for (i = 0; i < work->entryCount; i++) {
                    StageEntry *entry = &work->entries[i];

                    if ((entry->flags & STAGE_ENTRY_ENEMY) && entry->state != STAGE_ENTRY_OUT &&
                        entry->column == work->entries[FindStageEntryBySceneSlot(work->targetSlot)->index].column) {
                        VecFx32 position = entry->slot.node.position;

                        work->commandMarkers[markers++] = ShowStageMarker(3, &position, TRUE);
                    }
                }
            }
        } else {
            single = TRUE;
        }
        break;
    default:
        single = TRUE;
        break;
    }
    if (single) {
        if (work->commandMarkers[0] == NULL) {
            VecFx32 position =
                *SlotObjectPosition(&work->entries[FindStageEntryBySceneSlot(work->targetSlot)->index].slot.flags);

            work->commandMarkers[0] = ShowStageMarker(3, &position, TRUE);
        }
        switch (work->targetSlot) { /* slot 0 holds the second primary entry, slot 1 the first */
        case 0:
            UpdateMarkerScreenPosition(work->commandMarkers[0], SlotObjectPosition(&work->entries[1].slot.flags));
            return;
        case 1:
            UpdateMarkerScreenPosition(work->commandMarkers[0], &work->entries[0].slot.node.position);
            return;
        default:
            UpdateMarkerScreenPosition(
                work->commandMarkers[0],
                SlotObjectPosition(&work->entries[FindStageEntryBySceneSlot(work->targetSlot)->index].slot.flags));
            return;
        }
    }
}
