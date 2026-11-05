#include "nitro/types.h"

extern void WirelessMenu_LeaveState0Noop(void);
extern void ResetPanelSelection(void); /* ResetPanelSelection */
extern void UpdatePanelMenuState_02070c80(void); /* UpdatePanelMenuState */
extern void WirelessMenu_LeaveState1AndReleaseCursor(void); /* PXI_Init */
extern void InitWirelessMenuOwnerProfileView(void);
extern void UpdatePanelPendingAction(void); /* UpdatePanelPendingAction */
extern void WirelessMenu_LeaveOwnerProfileStateNoop(void);
extern void StartPlayerCardSharing(void); /* StartPlayerCardSharing */
extern void UpdatePanelShareState(void);
extern void WirelessMenu_LeaveState3AndReleaseCursor(void); /* PXI_Init */
extern void ClearOv002PanelModeDirtyFromWireless(void); /* OSi_IrqDma0 */
extern void DrawWirelessPanelHeaderAndEnterState1(void);
extern void WirelessMenu_LeaveHeaderStateNoop(void);
extern void OpenResultPanel(void); /* OpenResultPanel */
extern void FinishWirelessBoardViewWhenIntroEnds(void);
extern void RequestPanelConfirm(void); /* RequestPanelConfirm */
extern void ResetPanelEntry9(void); /* ResetPanelEntry9 */
extern void UpdatePanelResultPhase(void); /* UpdatePanelResultPhase */
extern void ClearPanelFlagE0Bit3(void);
extern void InitWirelessPanelConfirmWidgets(void);
extern void UpdatePanelConfirmSequence(void); /* UpdatePanelConfirmSequence */
extern void ResetPanelMenuElements(void); /* ResetPanelMenuElements */
extern void UpdatePanelExitSequence(void); /* UpdatePanelExitSequence */

void (*gLinkPanelStateHandlers[22])(void) = {
    WirelessMenu_LeaveState0Noop,
    ResetPanelSelection, /* ResetPanelSelection */
    UpdatePanelMenuState_02070c80, /* UpdatePanelMenuState */
    WirelessMenu_LeaveState1AndReleaseCursor, /* PXI_Init */
    InitWirelessMenuOwnerProfileView,
    UpdatePanelPendingAction, /* UpdatePanelPendingAction */
    WirelessMenu_LeaveOwnerProfileStateNoop,
    StartPlayerCardSharing, /* StartPlayerCardSharing */
    UpdatePanelShareState,
    WirelessMenu_LeaveState3AndReleaseCursor, /* PXI_Init */
    ClearOv002PanelModeDirtyFromWireless, /* OSi_IrqDma0 */
    DrawWirelessPanelHeaderAndEnterState1,
    WirelessMenu_LeaveHeaderStateNoop,
    OpenResultPanel, /* OpenResultPanel */
    FinishWirelessBoardViewWhenIntroEnds,
    RequestPanelConfirm, /* RequestPanelConfirm */
    ResetPanelEntry9, /* ResetPanelEntry9 */
    UpdatePanelResultPhase, /* UpdatePanelResultPhase */
    ClearPanelFlagE0Bit3,
    InitWirelessPanelConfirmWidgets,
    UpdatePanelConfirmSequence, /* UpdatePanelConfirmSequence */
    ResetPanelMenuElements, /* ResetPanelMenuElements */
};

void (*gLinkPanelExitHandler[1])(void) = {
    UpdatePanelExitSequence, /* UpdatePanelExitSequence */
};
