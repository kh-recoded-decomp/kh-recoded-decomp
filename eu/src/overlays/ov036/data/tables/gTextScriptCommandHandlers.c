#include "nitro/types.h"

extern void ScriptCmd_ResetAndDispatch(void); /* ScriptCmd_ResetAndDispatch */
extern void PanelScriptCmd_SetSlotSharedRecord(void); /* PXI_Init */
extern void PanelScriptCmd_MoveActorSlotX(void);
extern void PanelScriptCmd_StartActorSlotShake(void);
extern void PanelScriptCmd_ToggleActorSlotFlip(void); /* ScriptCmd_EnterPhase */
extern void PanelScriptCmd_StartActorFocusTransition(void);
extern void IsSceneState0_020bddb4(void); /* IsSceneState0 */
extern void ScriptCmd_OpenActorTextWindow(void); /* ScriptCmd_OpenActorTextWindow */
extern void ScriptCmd_OpenTextWindowAtCursor(void); /* ScriptCmd_OpenTextWindowAtCursor */
extern void ScriptCmd_OpenWindowAtPoint(void); /* ScriptCmd_OpenWindowAtPoint */
extern void ScriptCmd_WaitWindowChoice(void); /* ScriptCmd_WaitWindowChoice */
extern void PanelScriptCmd_CloseAllTextWindows(void); /* FS_UnloadOverlayImage */
extern void PanelScriptResume_CloseTextWindowsDone(void); /* DefaultStepDone */
extern void PanelScriptCmd_SetScreenLayerImage(void);
extern void ScriptCmd_WaitScreenLayerIdle(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void ScriptCmd_ResetScreenLayer(void); /* ScriptCmd_ResetScreenLayer */
extern void ScriptCmd_WaitScreenLayerIdle_020be118(void); /* ScriptCmd_WaitScreenLayerIdle */
extern void IsPxiResourceReadyOrInitialize(void); /* IsPxiResourceReadyOrInitialize */
extern void PanelScriptCmd_SetActorSlotPriority(void);
extern void PanelScriptCmd_StartActorSlotAlphaFade(void);
extern void PanelScriptCmd_ReleaseActorSlot(void); /* ScriptCmd_EnterPhase */
extern void PanelScriptCmd_MoveActorSlotY(void);
extern void ScriptCmd_ShowJoinedMessage(void); /* ScriptCmd_ShowJoinedMessage */
extern void ScriptCmd_ShowMessageWindow_020be284(void); /* ScriptCmd_ShowMessageWindow */
extern void ScriptCmd_ShowFormattedMessage(void);
extern void ScriptCmd_ShowNameList(void);
extern void ScriptCmd_WaitWindowAnswer(void); /* ScriptCmd_WaitWindowAnswer */
extern void PanelScriptCmd_StartScreenLayerScroll(void);
extern void ScriptCmd_ResetAndDispatch_020be55c(void); /* ScriptCmd_ResetAndDispatch */
extern void PanelScriptResume_LoadEntityModel(void); /* PXI_Init */
extern void ScriptCmd_PlaceEntityAndMove(void); /* ScriptCmd_PlaceEntityAndMove */
extern void ScriptCmd_SetEntityMotion(void); /* ScriptCmd_SetEntityMotion */
extern void PanelScriptCmd_ReleaseModelSlot(void);
extern void ScriptCmd_StartBrightnessFade(void); /* ScriptCmd_StartBrightnessFade */
extern void PanelScriptCmd_StartScreenLayerZoom(void);
extern void ScriptCmd_OpenFormattedTextWindow(void); /* ScriptCmd_OpenFormattedTextWindow */
extern void PanelScriptCmd_BeginWaitSoundState4Clear(void); /* FSi_CloseFileCommand */
extern void IsPanelScriptSoundWaitComplete(void); /* IsResourceReadyOrInitialize */
extern void ScriptCmd_StartMosaicTransition(void); /* ScriptCmd_StartMosaicTransition */
extern void IsSceneState0_020be7e0(void); /* IsSceneState0 */
extern void ScriptCmd_SetCursorOverride(void); /* ScriptCmd_SetCursorOverride */

void (*gTextScriptCommandHandlers[64])(void) = {
    ScriptCmd_ResetAndDispatch, /* ScriptCmd_ResetAndDispatch */
    PanelScriptCmd_SetSlotSharedRecord, /* PXI_Init */
    PanelScriptCmd_MoveActorSlotX,
    NULL,
    PanelScriptCmd_StartActorSlotShake,
    NULL,
    PanelScriptCmd_ToggleActorSlotFlip, /* ScriptCmd_EnterPhase */
    NULL,
    PanelScriptCmd_StartActorFocusTransition,
    IsSceneState0_020bddb4, /* IsSceneState0 */
    ScriptCmd_OpenActorTextWindow, /* ScriptCmd_OpenActorTextWindow */
    NULL,
    ScriptCmd_OpenTextWindowAtCursor, /* ScriptCmd_OpenTextWindowAtCursor */
    NULL,
    ScriptCmd_OpenWindowAtPoint, /* ScriptCmd_OpenWindowAtPoint */
    NULL,
    ScriptCmd_WaitWindowChoice, /* ScriptCmd_WaitWindowChoice */
    NULL,
    PanelScriptCmd_CloseAllTextWindows, /* FS_UnloadOverlayImage */
    PanelScriptResume_CloseTextWindowsDone, /* DefaultStepDone */
    PanelScriptCmd_SetScreenLayerImage,
    ScriptCmd_WaitScreenLayerIdle, /* ScriptCmd_WaitScreenLayerIdle */
    ScriptCmd_ResetScreenLayer, /* ScriptCmd_ResetScreenLayer */
    ScriptCmd_WaitScreenLayerIdle_020be118, /* ScriptCmd_WaitScreenLayerIdle */
    IsPxiResourceReadyOrInitialize, /* IsPxiResourceReadyOrInitialize */
    NULL,
    PanelScriptCmd_SetActorSlotPriority,
    NULL,
    PanelScriptCmd_StartActorSlotAlphaFade,
    NULL,
    PanelScriptCmd_ReleaseActorSlot, /* ScriptCmd_EnterPhase */
    NULL,
    PanelScriptCmd_MoveActorSlotY,
    NULL,
    ScriptCmd_ShowJoinedMessage, /* ScriptCmd_ShowJoinedMessage */
    NULL,
    ScriptCmd_ShowMessageWindow_020be284, /* ScriptCmd_ShowMessageWindow */
    NULL,
    ScriptCmd_ShowFormattedMessage,
    NULL,
    ScriptCmd_ShowNameList,
    ScriptCmd_WaitWindowAnswer, /* ScriptCmd_WaitWindowAnswer */
    PanelScriptCmd_StartScreenLayerScroll,
    NULL,
    ScriptCmd_ResetAndDispatch_020be55c, /* ScriptCmd_ResetAndDispatch */
    PanelScriptResume_LoadEntityModel, /* PXI_Init */
    ScriptCmd_PlaceEntityAndMove, /* ScriptCmd_PlaceEntityAndMove */
    NULL,
    ScriptCmd_SetEntityMotion, /* ScriptCmd_SetEntityMotion */
    NULL,
    PanelScriptCmd_ReleaseModelSlot,
    NULL,
    ScriptCmd_StartBrightnessFade, /* ScriptCmd_StartBrightnessFade */
    NULL,
    PanelScriptCmd_StartScreenLayerZoom,
    NULL,
    ScriptCmd_OpenFormattedTextWindow, /* ScriptCmd_OpenFormattedTextWindow */
    NULL,
    PanelScriptCmd_BeginWaitSoundState4Clear, /* FSi_CloseFileCommand */
    IsPanelScriptSoundWaitComplete, /* IsResourceReadyOrInitialize */
    ScriptCmd_StartMosaicTransition, /* ScriptCmd_StartMosaicTransition */
    IsSceneState0_020be7e0, /* IsSceneState0 */
    ScriptCmd_SetCursorOverride, /* ScriptCmd_SetCursorOverride */
    NULL,
};
