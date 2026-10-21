#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_B 0x0002

extern u16 data_02060500;
extern void RequestFieldRefresh(void);
extern void ShowStageHudMessage(u8 kind, ...);
extern void func_ov041_020be478(int arg);
extern StageEntry *FindStageEntryBySceneSlot(int sceneSlot);
extern void ReleaseCommandMarkers(void);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void ForceHudState6IfActive(void);
extern void HideStageHudMessage(void);
extern void SetStageState(int state, BOOL runNow);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state 14: target choice for an item. Puts the cursor on the first entry still in the fight on the side
 * the item is for; items 0xb7/0xb8 show HUD message 11. A confirms (items 0xe4-0xe6 aim every primary entry at
 * the target, others only the first) and moves on to state 15; B goes back to the menu (state 6).
 */
void StageStateChooseItemTarget(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    switch (work->stateStep) {
    case 0:
        RequestFieldRefresh();
        work->stateStep++;
    case 1:
        work->stateStep++;
    case 2:
        if (work->itemEffectKind < 7) {
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
        switch (work->itemId) {
        case 0xb7:
        case 0xb8:
            ShowStageHudMessage(11, work->itemId, 0);
            break;
        }
    default:
        func_ov041_020be478(0);
        if (data_02060500 & PAD_BUTTON_A) {
            switch (work->itemId) {
            case 0xe4:
            case 0xe5:
            case 0xe6:
                for (i = 0; i < work->primaryCount; i++) {
                    work->entries[i].mainTarget = FindStageEntryBySceneSlot(work->targetSlot)->index;
                }
                break;
            default:
                work->entries[0].mainTarget = FindStageEntryBySceneSlot(work->targetSlot)->index;
                break;
            }
            ReleaseCommandMarkers();
            PlayStageSound(0, 1, FALSE);
            SetStageState(15, FALSE);
        } else if (data_02060500 & PAD_BUTTON_B) {
            ReleaseCommandMarkers();
            ForceHudState6IfActive();
            HideStageHudMessage();
            PlayStageSound(0, 3, FALSE);
            SetStageState(6, FALSE);
        }
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
