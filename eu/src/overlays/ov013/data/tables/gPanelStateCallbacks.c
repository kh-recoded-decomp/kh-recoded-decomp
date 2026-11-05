#include "src/overlays/ov013/Ov013PanelState.h"

extern void ResolvePanelExitMode(void);
extern void UpdatePanelEntryState(void);
extern void SetOv002PanelStateFlag4FromOv013(void);
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
extern void Ov013Panel_LeaveSaveStateNoop(void);
extern void CloseRecordPanelMenu(void);
extern void UpdatePanelMenuState(void);
extern void RefreshPanelSlotLinks(void);
extern void ClosePanelMenu(void);
extern void UpdatePanelBrowseState(void);
extern void ClearPanelListCallback(void);
extern void BeginOv013PlayerCardPageTransition(void);
extern void AdvancePanelCloseStep(void);
extern void Ov013Panel_LeavePlayerCardTransitionNoop(void);
extern void ResetPanelListUpStep(void);
extern void UpdateOv013HeldScrollTowardStart(void);
extern void Ov013Panel_LeaveHeldScrollTowardStartNoop(void);
extern void ResetPanelListDownStep(void);
extern void UpdateOv013HeldScrollTowardEnd(void);
extern void Ov013Panel_LeaveHeldScrollTowardEndNoop(void);
extern void OpenPanelConfirmPrompt(void);
extern void UpdatePanelDismissPrompt(void);
extern void RestorePanelBgPriorities(void);

/* Each mode has an entry action, a per-frame update and an exit action. */
PanelStateCallbacks gPanelStateCallbacks[12] = {
    { ResolvePanelExitMode, UpdatePanelEntryState, SetOv002PanelStateFlag4FromOv013 },
    { ResetPanelStepAndNotify, UpdatePanelScrollState, ApplyPanelSubitem5 },
    { OpenPanelSelectionMenu, UpdatePanelResultState, ResetPanelLayoutClearFlag },
    { RefreshSelectedSlotFlags, UpdateSlotRemovalPhase, CancelPanelConfirm },
    { OpenPanelResultMenu, UpdatePanelResultPrompt, ResetPanelLayout },
    { ResetPanelSaveStep, PollPanelSaveStep, Ov013Panel_LeaveSaveStateNoop },
    { CloseRecordPanelMenu, UpdatePanelMenuState, RefreshPanelSlotLinks },
    { ClosePanelMenu, UpdatePanelBrowseState, ClearPanelListCallback },
    { BeginOv013PlayerCardPageTransition, AdvancePanelCloseStep, Ov013Panel_LeavePlayerCardTransitionNoop },
    { ResetPanelListUpStep, UpdateOv013HeldScrollTowardStart, Ov013Panel_LeaveHeldScrollTowardStartNoop },
    { ResetPanelListDownStep, UpdateOv013HeldScrollTowardEnd, Ov013Panel_LeaveHeldScrollTowardEndNoop },
    { OpenPanelConfirmPrompt, UpdatePanelDismissPrompt, RestorePanelBgPriorities },
};
