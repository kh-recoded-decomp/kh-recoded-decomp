#include "nitro/types.h"

extern void AdvancePanelCloseStep_02073944(void);
extern void ApplyPanelSubitem5_02072228(void);
extern void CancelPanelConfirm_020731a4(void);
extern void ClearPanelListCallback_020738ec(void);
extern void ClosePanelMenu_020735d0(void);
extern void CloseRecordPanelMenu_020732a8(void);
extern void OpenPanelConfirmPrompt_02073b94(void);
extern void PXI_Init_02071a90(void);
extern void PollPanelSaveStep_0207324c(void);
extern void RefreshPanelSlotLinks_02073548(void);
extern void RefreshSelectedSlotFlags_02072c18(void);
extern void ResetPanelLayoutClearFlag_02072674(void);
extern void ResetPanelLayout_02072ae8(void);
extern void ResetPanelStepAndNotify_02071a9c(void);
extern void RestorePanelBgPriorities_02073e38(void);
extern void UpdatePanelBrowseState_0207370c(void);
extern void UpdatePanelDismissPrompt_02073d14(void);
extern void UpdatePanelEntryState_020718e0(void);
extern void UpdatePanelMenuState_020733f0(void);
extern void UpdatePanelResultPrompt_020729e4(void);
extern void UpdatePanelResultState_020724c0(void);
extern void UpdateSlotRemovalPhase_02072d0c(void);
extern void func_ov013_02071b6c(void);
extern void func_ov013_0207225c(void);
extern void func_ov013_020727b4(void);
extern void func_ov013_02073234(void);
extern void func_ov013_020732a4(void);
extern void func_ov013_0207390c(void);
extern void func_ov013_020739a0(void);
extern void func_ov013_020739a4(void);
extern void func_ov013_020739bc(void);
extern void func_ov013_02073a98(void);
extern void func_ov013_02073a9c(void);
extern void func_ov013_02073ab4(void);
extern void func_ov013_02073b90(void);

void (*data_ov013_02074bc4[34])(void) = {
    PXI_Init_02071a90,
    ResetPanelStepAndNotify_02071a9c,
    func_ov013_02071b6c,
    ApplyPanelSubitem5_02072228,
    func_ov013_0207225c,
    UpdatePanelResultState_020724c0,
    ResetPanelLayoutClearFlag_02072674,
    RefreshSelectedSlotFlags_02072c18,
    UpdateSlotRemovalPhase_02072d0c,
    CancelPanelConfirm_020731a4,
    func_ov013_020727b4,
    UpdatePanelResultPrompt_020729e4,
    ResetPanelLayout_02072ae8,
    func_ov013_02073234,
    PollPanelSaveStep_0207324c,
    func_ov013_020732a4,
    CloseRecordPanelMenu_020732a8,
    UpdatePanelMenuState_020733f0,
    RefreshPanelSlotLinks_02073548,
    ClosePanelMenu_020735d0,
    UpdatePanelBrowseState_0207370c,
    ClearPanelListCallback_020738ec,
    func_ov013_0207390c,
    AdvancePanelCloseStep_02073944,
    func_ov013_020739a0,
    func_ov013_020739a4,
    func_ov013_020739bc,
    func_ov013_02073a98,
    func_ov013_02073a9c,
    func_ov013_02073ab4,
    func_ov013_02073b90,
    OpenPanelConfirmPrompt_02073b94,
    UpdatePanelDismissPrompt_02073d14,
    RestorePanelBgPriorities_02073e38,
};

void (*data_ov013_02074bc0[1])(void) = {
    UpdatePanelEntryState_020718e0,
};
