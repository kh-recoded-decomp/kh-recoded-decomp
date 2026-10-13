#include "src/overlays/ov013/Ov013PanelState.h"

extern void ResolvePanelExitMode(void);
extern void UpdatePanelEntryState(void);
extern void func_ov013_02071a90(void);
extern void ResetPanelStepAndNotify(void);
extern void UpdatePanelScrollState(void);
extern void ApplyPanelSubitem5(void);
extern void OpenPanelSelectionMenu(void);
extern void UpdatePanelResultState(void);
extern void ResetPanelLayoutClearFlag(void);
extern void RefreshSelectedSlotFlags(void);
extern void UpdateSlotRemovalPhase(void);
extern void CancelPanelConfirm(void);
extern void OpenPanelResultMenu(void);
extern void UpdatePanelResultPrompt(void);
extern void ResetPanelLayout(void);
extern void ResetPanelSaveStep(void);
extern void PollPanelSaveStep(void);
extern void func_ov013_020732a4(void);
extern void CloseRecordPanelMenu(void);
extern void UpdatePanelMenuState(void);
extern void RefreshPanelSlotLinks(void);
extern void ClosePanelMenu(void);
extern void UpdatePanelBrowseState(void);
extern void ClearPanelListCallback(void);
extern void func_ov013_0207390c(void);
extern void AdvancePanelCloseStep(void);
extern void func_ov013_020739a0(void);
extern void ResetPanelListUpStep(void);
extern void func_ov013_020739bc(void);
extern void func_ov013_02073a98(void);
extern void ResetPanelListDownStep(void);
extern void func_ov013_02073ab4(void);
extern void func_ov013_02073b90(void);
extern void OpenPanelConfirmPrompt(void);
extern void UpdatePanelDismissPrompt(void);
extern void RestorePanelBgPriorities(void);

/* Each mode has an entry action, a per-frame update and an exit action. */
PanelStateCallbacks gPanelStateCallbacks[12] = {
    { ResolvePanelExitMode, UpdatePanelEntryState, func_ov013_02071a90 },
    { ResetPanelStepAndNotify, UpdatePanelScrollState, ApplyPanelSubitem5 },
    { OpenPanelSelectionMenu, UpdatePanelResultState, ResetPanelLayoutClearFlag },
    { RefreshSelectedSlotFlags, UpdateSlotRemovalPhase, CancelPanelConfirm },
    { OpenPanelResultMenu, UpdatePanelResultPrompt, ResetPanelLayout },
    { ResetPanelSaveStep, PollPanelSaveStep, func_ov013_020732a4 },
    { CloseRecordPanelMenu, UpdatePanelMenuState, RefreshPanelSlotLinks },
    { ClosePanelMenu, UpdatePanelBrowseState, ClearPanelListCallback },
    { func_ov013_0207390c, AdvancePanelCloseStep, func_ov013_020739a0 },
    { ResetPanelListUpStep, func_ov013_020739bc, func_ov013_02073a98 },
    { ResetPanelListDownStep, func_ov013_02073ab4, func_ov013_02073b90 },
    { OpenPanelConfirmPrompt, UpdatePanelDismissPrompt, RestorePanelBgPriorities },
};
