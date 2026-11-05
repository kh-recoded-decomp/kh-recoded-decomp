#include "nitro/types.h"

extern void StopTouchPanelSampling(void); /* StopTouchPanelSampling */
extern void ApplyPanelSelection(void); /* ApplyPanelSelection */
extern void UpdateTitleTimedPanelPhase(void);
extern void InitPanelSceneAndClearBg1(void); /* InitPanelSceneAndClearBg1 */
extern void WaitForAnimationFinish(void); /* WaitForAnimationFinish */
extern void ForceReleaseEmbedded(void); /* ForceReleaseEmbedded */
extern void ResetPanelStateAndLoadSlot0(void); /* ResetPanelStateAndLoadSlot0 */
extern void ScanSaveSlots(void); /* ScanSaveSlots */
extern void ApplyTitleMenuFlagsAndStoreLanguage(void);
extern void EnterPanelMenuScreen(void); /* EnterPanelMenuScreen */
extern void UpdatePanelInputWithTimeout(void); /* UpdatePanelInputWithTimeout */
extern void ReleaseTitlePanelResources(void); /* NNS_G2dSetCellAnimationSequence */
extern void FinishTitlePanel(void);
extern void TryEnterPanelState(void); /* TryEnterPanelState */
extern void RecordTitleStartTickWrapper(void); /* PXI_Init */
extern void SetupPanelField(void); /* SetupPanelField */
extern void WaitPanelWorldSession(void);
extern void ReleaseFieldAndReset(void); /* ReleaseFieldAndReset */
extern void UpdatePanelLookup(void); /* UpdatePanelLookup */
extern void HandleSessionModeTransition(void); /* HandleSessionModeTransition */
extern void ReleaseHandleAndResetDisplay(void); /* ReleaseHandleAndResetDisplay */
extern void LoadOverlay22AndClearFlag(void);
extern void UpdatePanelRequest(void); /* UpdatePanelRequest */
extern void ShutdownTitlePanel(void);
extern void LoadOverlay3AndClearFlag(void);
extern void UpdateTitleOverlayLoad(void);
extern void ReleaseTitleOverlayTask(void);
extern void BeginTitleSaveFormat(void);
extern void WaitTitleSaveFormat(void);
extern void SetupTitleDisplayBanksAndLayersWrapper(void); /* PXI_Init */
extern void ShowTitleFormatNotice(void);
extern void UpdateTitleFormatNoticeKeepState(void);
extern void LeaveTitleFormatNoticeNoop(void);

void (*gPanelStateHandlers[43])(void) = {
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    UpdateTitleTimedPanelPhase,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    UpdateTitleTimedPanelPhase,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    ApplyPanelSelection, /* ApplyPanelSelection */
    UpdateTitleTimedPanelPhase,
    StopTouchPanelSampling, /* StopTouchPanelSampling */
    InitPanelSceneAndClearBg1, /* InitPanelSceneAndClearBg1 */
    WaitForAnimationFinish, /* WaitForAnimationFinish */
    ForceReleaseEmbedded, /* ForceReleaseEmbedded */
    ResetPanelStateAndLoadSlot0, /* ResetPanelStateAndLoadSlot0 */
    ScanSaveSlots, /* ScanSaveSlots */
    ApplyTitleMenuFlagsAndStoreLanguage,
    EnterPanelMenuScreen, /* EnterPanelMenuScreen */
    UpdatePanelInputWithTimeout, /* UpdatePanelInputWithTimeout */
    ReleaseTitlePanelResources, /* NNS_G2dSetCellAnimationSequence */
    FinishTitlePanel,
    TryEnterPanelState, /* TryEnterPanelState */
    RecordTitleStartTickWrapper, /* PXI_Init */
    SetupPanelField, /* SetupPanelField */
    WaitPanelWorldSession,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    SetupPanelField, /* SetupPanelField */
    WaitPanelWorldSession,
    ReleaseFieldAndReset, /* ReleaseFieldAndReset */
    UpdatePanelLookup, /* UpdatePanelLookup */
    HandleSessionModeTransition, /* HandleSessionModeTransition */
    ReleaseHandleAndResetDisplay, /* ReleaseHandleAndResetDisplay */
    LoadOverlay22AndClearFlag,
    UpdatePanelRequest, /* UpdatePanelRequest */
    ShutdownTitlePanel,
    LoadOverlay3AndClearFlag,
    UpdateTitleOverlayLoad,
    ReleaseTitleOverlayTask,
    BeginTitleSaveFormat,
    WaitTitleSaveFormat,
    SetupTitleDisplayBanksAndLayersWrapper, /* PXI_Init */
    ShowTitleFormatNotice,
    UpdateTitleFormatNoticeKeepState,
    LeaveTitleFormatNoticeNoop,
};

void (*gPanelInitialStateHandler[1])(void) = {
    UpdateTitleTimedPanelPhase,
};
