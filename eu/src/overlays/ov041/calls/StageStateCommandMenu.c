#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"
#include "src/overlays/ov041/StageCaption.h"

#define PAD_BUTTON_A 0x0001
#define PAD_BUTTON_B 0x0002
#define PAD_BUTTON_R 0x0100
#define PAD_BUTTON_L 0x0200
#define PAD_BUTTON_X 0x0400

extern int data_ov041_020cff40[2]; /* [0] a short wait, [1] frames R has been held */
extern u16 data_020604fc; /* buttons held */
extern u16 data_02060500; /* buttons newly pressed */
extern void ForceHudState6IfActive(void);
extern void HideStageHudMessage(void);
extern BOOL func_ov001_02077ef4(void);
extern void HandleCommandMenuShortcuts(BOOL canSwitchMode);
extern void ShowStageHudMessage(u8 kind, ...);
extern void SetMenuEntryHighlight(int listKind, int entryId, BOOL highlighted);
extern int InvokeFieldModeOp150(void);
extern void ResetSlotHandles(void);
extern int GetSelectedMenuEntryValue(void);
extern s32 func_ov001_02078494(void);
extern void SelectFieldMenuPage(int page);
extern void PlayStageSound(int seqArcNo, int index, BOOL checked);
extern void SetStageState(int state, BOOL runNow);
extern BOOL IsMenuItemAssigned(int itemId);
extern int ApplyCurrentFieldMode(u16 entry);
extern int ResolveEventVariant(int eventId);
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern s32 func_ov001_020789b8(s32 id);
extern StageHudEntry *GetHudEntry(int id);
extern s16 *GetPlayerFlagRecord(int index);
extern void UpdateStageEntry(u8 entryIndex);

/*
 * Stage state for the command menu: after a two-frame wait it runs the shortcuts (HandleCommandMenuShortcuts), then
 * reads the menu: holding R for 30 frames closes every submenu and flees (state 8), B backs out of a submenu,
 * A goes to state 7; X picks the highlighted entry, which opens a submenu (up to three deep), uses an item
 * (state 14, with the item's action loaded) or, outside the main page, a command (state 12). Entries are
 * updated every frame.
 */
void StageStateCommandMenu(void)
{
    int i;
    int chosen;
    StageWork *work;
    int action; /* the item action to load */

    work = gMovieContextState->stageWork;
    chosen = -1;

    switch (work->stateStep) {
    case 0:
        ForceHudState6IfActive();
        HideStageHudMessage();
        if (work->flags & STAGE_WORK_TURN_STARTED) {
            func_ov001_02077ef4();
            work->flags &= ~STAGE_WORK_TURN_STARTED;
        }
        data_ov041_020cff40[0] = 2;
        work->stateStep++;
    case 1:
        if (data_ov041_020cff40[0] > 0) {
            data_ov041_020cff40[0]--;
            break;
        }
        work->stateStep++;
    case 2:
        HandleCommandMenuShortcuts(TRUE);
        if (data_020604fc & PAD_BUTTON_R) {
            data_ov041_020cff40[1]++;
            work->flags |= 0x100;
            if (work->flags & STAGE_WORK_SKIP_CHANCE_A) {
                ShowStageHudMessage(4);
            }
            if (data_ov041_020cff40[1] > 30) {
                for (i = 0; i < work->menuDepth; i++) {
                    SetMenuEntryHighlight(0, work->menuStack[i], TRUE);
                    InvokeFieldModeOp150();
                }
                ResetSlotHandles();
                HideStageHudMessage();
                data_ov041_020cff40[1] = 0;
                work->flags |= STAGE_WORK_NO_TIMED_INPUT;
                SetStageState(8, TRUE);
            }
        } else if (!(data_020604fc & PAD_BUTTON_L)) {
            data_ov041_020cff40[1] = 0;
            work->flags &= ~0x100;
            HideStageHudMessage();
            if (data_02060500 & PAD_BUTTON_X) {
                chosen = GetSelectedMenuEntryValue();
            } else if (data_02060500 & PAD_BUTTON_B) {
                if (func_ov001_02078494() == 0 && work->menuDepth > 0) {
                    work->menuDepth = InvokeFieldModeOp150();
                    SetMenuEntryHighlight(0, work->menuStack[work->menuDepth], TRUE);
                    work->menuStack[work->menuDepth] = -1;
                    if (work->menuDepth == 0) {
                        SelectFieldMenuPage(0);
                    }
                    PlayStageSound(0, 3, FALSE);
                }
            } else if (data_02060500 & PAD_BUTTON_A) {
                PlayStageSound(0, 1, FALSE);
                SetStageState(7, FALSE);
            }
        }
        if (chosen < 0) {
            break;
        }
        if (func_ov001_02078494() == 0) {
            if (IsMenuItemAssigned(chosen)) {
                if (work->menuDepth == 0) {
                    SelectFieldMenuPage(0xc);
                }
                if (work->menuDepth < 3) {
                    work->menuDepth = ApplyCurrentFieldMode(chosen);
                    work->menuStack[work->menuDepth - 1] = chosen;
                    PlayStageSound(0, 1, FALSE);
                    SetMenuEntryHighlight(func_ov001_02078494(), chosen, FALSE);
                    func_ov001_02077ef4();
                }
                break;
            }
            switch (ResolveEventVariant(chosen)) {
            case 0xb7:
                action = 0x18;
                break;
            case 0xb8:
                action = 0x19;
                break;
            }
            MIi_CpuCopyFast(&work->itemActionTable->actions[action], &work->itemActions[0], sizeof(StageEntryAction));
            work->itemActions[0].itemSlot = chosen;
            work->itemActions[0].effect = ResolveEventVariant(chosen);
            work->itemActions[0].effectArg = GetHudEntry(func_ov001_020789b8(chosen))->rows;
            PlayStageSound(0, 1, FALSE);
            SetStageState(0xe, FALSE);
        } else if (chosen >= 0) {
            work->fieldSlot = chosen;
            work->commandId = *GetPlayerFlagRecord(work->fieldSlot);
            PlayStageSound(0, 1, FALSE);
            switch (work->commandId) {
            case 0xd4:
            case 0xd5:
                work->targetIndex = 0;
                SetStageState(0xc, FALSE);
                break;
            default:
                SetStageState(0xc, FALSE);
                break;
            }
        }
        break;
    }
    for (i = 0; i < work->entryCount; i++) {
        UpdateStageEntry(i);
    }
}
