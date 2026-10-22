#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_B 0x0002

extern u16 data_02060500;
extern void RequestFieldRefresh(void);
extern void InvokeFieldModeOp2c4(int commandId);
extern int GetCommandEffectKind(int commandId);
extern StageMarker *ShowStageMarker(int listIndex, const VecFx32 *position, BOOL persistent);
extern void MoveTargetCursor(int source);
extern StageEntry *FindStageEntryBySceneSlot(int sceneSlot);
extern void ReleaseCommandMarkers(void);
extern void SetStageState(int state, BOOL runNow);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void ForceHudState6IfActive(void);
extern void InvokeFieldModeOp340(void);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 12: target choice for the chosen command. Puts the cursor on the first entry still in the fight on
 * the side the command is for (secondary entries for effect kinds below 7, primary ones otherwise); A confirms
 * the target (state 13), B goes back to the command menu (state 6). Every entry is updated each frame.
 */
void StageStateChooseTarget(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;
    VecFx32 position;

    switch (work->stateStep) {
    case 0:
        RequestFieldRefresh();
        InvokeFieldModeOp2c4(work->commandId);
        work->stateStep++;
    case 1:
        work->commandEffectKind = GetCommandEffectKind(work->commandId);
        position = work->entries[0].slot.node.position;
        work->commandMarkers[0] = ShowStageMarker(3, &position, TRUE);
        work->stateStep++;
    case 2:
        if (work->commandEffectKind < 7) {
            for (i = 0; i < work->secondaryCount; i++) {
                if ((work->entries + work->primaryCount)[i].state != STAGE_ENTRY_OUT) {
                    work->targetSlot = work->entries[i + work->primaryCount].sceneSlot;
                    break;
                }
            }
        } else {
            for (i = 0; i < work->primaryCount; i++) {
                if (work->entries[i].state != STAGE_ENTRY_OUT) {
                    work->targetSlot = work->entries[i].sceneSlot;
                    break;
                }
            }
        }
        work->stateStep++;
    case 3:
    default:
        MoveTargetCursor(1);
        if (data_02060500 & PAD_BUTTON_A) {
            work->targetIndex = FindStageEntryBySceneSlot(work->targetSlot)->index;
            ReleaseCommandMarkers();
            SetStageState(13, FALSE);
            PlayStageSound(0, 1, FALSE);
        } else if (data_02060500 & PAD_BUTTON_B) {
            ReleaseCommandMarkers();
            ForceHudState6IfActive();
            InvokeFieldModeOp340();
            PlayStageSound(0, 3, FALSE);
            SetStageState(6, FALSE);
        }
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
