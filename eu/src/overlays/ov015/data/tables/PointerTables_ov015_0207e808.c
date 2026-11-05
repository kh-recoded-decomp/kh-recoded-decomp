#include "nitro/types.h"

extern void WirelessConnection_LeaveState0Noop(void);
extern void WirelessConnection_EnterState1Noop(void);
extern void WirelessConnection_UpdateState1Noop(void);
extern void WirelessConnection_LeaveState1Noop(void);
extern void FinalizeWirelessConnectionWrapper(void); /* PXI_Init */
extern void DispatchPanelTransition(void); /* DispatchPanelTransition */
extern void SetWirelessReadyFlag(void);
extern void WirelessConnection_EnterState3Noop(void);
extern void HandleMatchTransition(void); /* HandleMatchTransition */
extern void WirelessConnection_LeaveState3Noop(void);
extern void WirelessConnection_EnterState4Noop(void);
extern void UpdateWirelessParentState(void); /* UpdateWirelessParentState */
extern void WirelessConnection_LeaveState4Noop(void);
extern void WirelessConnection_EnterState5Noop(void);
extern void HandleConnectTransition(void); /* HandleConnectTransition */
extern void WirelessConnection_LeaveState5Noop(void);
extern void StartWirelessFinalizeDelay16(void);
extern void PollWirelessFinalizeDelay17(void);
extern void WirelessConnection_LeaveState6Noop(void);
extern void StartWirelessFinalizeDelay19(void);
extern void PollWirelessFinalizeDelay20(void);
extern void WirelessConnection_LeaveState7Noop(void);
extern void EnterWirelessConnectionState3UnlessHelperState3(void);

void (*gWirelessStateHandlers[22])(void) = {
    WirelessConnection_LeaveState0Noop,
    WirelessConnection_EnterState1Noop,
    WirelessConnection_UpdateState1Noop,
    WirelessConnection_LeaveState1Noop,
    FinalizeWirelessConnectionWrapper, /* PXI_Init */
    DispatchPanelTransition, /* DispatchPanelTransition */
    SetWirelessReadyFlag,
    WirelessConnection_EnterState3Noop,
    HandleMatchTransition, /* HandleMatchTransition */
    WirelessConnection_LeaveState3Noop,
    WirelessConnection_EnterState4Noop,
    UpdateWirelessParentState, /* UpdateWirelessParentState */
    WirelessConnection_LeaveState4Noop,
    WirelessConnection_EnterState5Noop,
    HandleConnectTransition, /* HandleConnectTransition */
    WirelessConnection_LeaveState5Noop,
    StartWirelessFinalizeDelay16,
    PollWirelessFinalizeDelay17,
    WirelessConnection_LeaveState6Noop,
    StartWirelessFinalizeDelay19,
    PollWirelessFinalizeDelay20,
    WirelessConnection_LeaveState7Noop,
};

void (*gWirelessStateUpdateCallback[1])(void) = {
    EnterWirelessConnectionState3UnlessHelperState3,
};
