#include "nitro/types.h"

extern void ApplyPanelSelection_020622b8(void);
extern void EnterPanelMenuScreen_02062794(void);
extern void ForceReleaseEmbedded_02062598(void);
extern void HandleSessionModeTransition_02062c64(void);
extern void InitPanelSceneAndClearBg1_0206243c(void);
extern void LoadOverlay22AndClearFlag_02062d38(void);
extern void NNS_G2dSetCellAnimationSequence_02062908(void);
extern void PXI_Init_02062a58(void);
extern void PXI_Init_0206300c(void);
extern void ReleaseFieldAndReset_02062bdc(void);
extern void ReleaseHandleAndResetDisplay_02062cf4(void);
extern void ResetPanelStateAndLoadSlot0_020625b0(void);
extern void ScanSaveSlots_020625d4(void);
extern void SetupPanelField_02062a64(void);
extern void StopTouchPanelSampling_0206241c(void);
extern void TryEnterPanelState_02062a10(void);
extern void UpdatePanelInputWithTimeout_02062838(void);
extern void UpdatePanelLookup_02062c08(void);
extern void UpdatePanelRequest_02062d60(void);
extern void WaitForAnimationFinish_02062568(void);
extern void func_ov000_02062318(void);
extern void func_ov000_0206276c(void);
extern void func_ov000_02062920(void);
extern void func_ov000_02062a98(void);
extern void func_ov000_02062e00(void);
extern void func_ov000_02062e3c(void);
extern void func_ov000_02062e64(void);
extern void func_ov000_02062f0c(void);
extern void func_ov000_02062f44(void);
extern void func_ov000_02062f74(void);
extern void func_ov000_02063018(void);
extern void func_ov000_02063038(void);
extern void func_ov000_02063040(void);

void (*data_ov000_0206388c[43])(void) = {
    StopTouchPanelSampling_0206241c,
    ApplyPanelSelection_020622b8,
    func_ov000_02062318,
    StopTouchPanelSampling_0206241c,
    ApplyPanelSelection_020622b8,
    func_ov000_02062318,
    StopTouchPanelSampling_0206241c,
    ApplyPanelSelection_020622b8,
    func_ov000_02062318,
    StopTouchPanelSampling_0206241c,
    InitPanelSceneAndClearBg1_0206243c,
    WaitForAnimationFinish_02062568,
    ForceReleaseEmbedded_02062598,
    ResetPanelStateAndLoadSlot0_020625b0,
    ScanSaveSlots_020625d4,
    func_ov000_0206276c,
    EnterPanelMenuScreen_02062794,
    UpdatePanelInputWithTimeout_02062838,
    NNS_G2dSetCellAnimationSequence_02062908,
    func_ov000_02062920,
    TryEnterPanelState_02062a10,
    PXI_Init_02062a58,
    SetupPanelField_02062a64,
    func_ov000_02062a98,
    ReleaseFieldAndReset_02062bdc,
    SetupPanelField_02062a64,
    func_ov000_02062a98,
    ReleaseFieldAndReset_02062bdc,
    UpdatePanelLookup_02062c08,
    HandleSessionModeTransition_02062c64,
    ReleaseHandleAndResetDisplay_02062cf4,
    LoadOverlay22AndClearFlag_02062d38,
    UpdatePanelRequest_02062d60,
    func_ov000_02062e00,
    func_ov000_02062e3c,
    func_ov000_02062e64,
    func_ov000_02062f0c,
    func_ov000_02062f44,
    func_ov000_02062f74,
    PXI_Init_0206300c,
    func_ov000_02063018,
    func_ov000_02063038,
    func_ov000_02063040,
};

void (*data_ov000_02063888[1])(void) = {
    func_ov000_02062318,
};
