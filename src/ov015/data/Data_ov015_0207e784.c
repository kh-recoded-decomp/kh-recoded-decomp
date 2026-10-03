#include "nitro/types.h"

extern void OSi_IrqDma0_02071a78(void);
extern void OpenResultPanel_02071ab4(void);
extern void PXI_Init_02070fa8(void);
extern void PXI_Init_020716ec(void);
extern void RequestPanelConfirm_02071c60(void);
extern void ResetPanelEntry9_02071ca8(void);
extern void ResetPanelMenuElements_020720e4(void);
extern void ResetPanelSelection_02070c58(void);
extern void StartPlayerCardSharing_02071064(void);
extern void UpdatePanelConfirmSequence_02071fdc(void);
extern void UpdatePanelExitSequence_02070b8c(void);
extern void UpdatePanelMenuState_02070c80(void);
extern void UpdatePanelPendingAction_02070fe8(void);
extern void UpdatePanelResultPhase_02071d0c(void);
extern void func_ov015_02070c54(void);
extern void func_ov015_02070fb4(void);
extern void func_ov015_02071060(void);
extern void func_ov015_02071100(void);
extern void func_ov015_02071a88(void);
extern void func_ov015_02071ab0(void);
extern void func_ov015_02071bec(void);
extern void func_ov015_02071e2c(void);
extern void func_ov015_02071e48(void);

void (*data_ov015_0207e788[22])(void) = {
    func_ov015_02070c54,
    ResetPanelSelection_02070c58,
    UpdatePanelMenuState_02070c80,
    PXI_Init_02070fa8,
    func_ov015_02070fb4,
    UpdatePanelPendingAction_02070fe8,
    func_ov015_02071060,
    StartPlayerCardSharing_02071064,
    func_ov015_02071100,
    PXI_Init_020716ec,
    OSi_IrqDma0_02071a78,
    func_ov015_02071a88,
    func_ov015_02071ab0,
    OpenResultPanel_02071ab4,
    func_ov015_02071bec,
    RequestPanelConfirm_02071c60,
    ResetPanelEntry9_02071ca8,
    UpdatePanelResultPhase_02071d0c,
    func_ov015_02071e2c,
    func_ov015_02071e48,
    UpdatePanelConfirmSequence_02071fdc,
    ResetPanelMenuElements_020720e4,
};

void (*data_ov015_0207e784[1])(void) = {
    UpdatePanelExitSequence_02070b8c,
};
