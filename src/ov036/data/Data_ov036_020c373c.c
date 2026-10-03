#include "nitro/types.h"

extern void DefaultStepDone_020be084(void);
extern void FS_UnloadOverlayImage_020be078(void);
extern void FSi_CloseFileCommand_020be76c(void);
extern void IsPxiResourceReadyOrInitialize_020be110(void);
extern void IsResourceReadyOrInitialize_020be770(void);
extern void IsSceneState0_020bdd94(void);
extern void IsSceneState0_020be7c0(void);
extern void PXI_Init_020bdce8(void);
extern void PXI_Init_020be55c(void);
extern void ScriptCmd_EnterPhase_020bdd54(void);
extern void ScriptCmd_EnterPhase_020be190(void);
extern void ScriptCmd_OpenActorTextWindow_020bde08(void);
extern void ScriptCmd_OpenFormattedTextWindow_020be69c(void);
extern void ScriptCmd_OpenTextWindowAtCursor_020bdecc(void);
extern void ScriptCmd_OpenWindowAtPoint_020bdf88(void);
extern void ScriptCmd_PlaceEntityAndMove_020be564(void);
extern void ScriptCmd_ResetAndDispatch_020bdcc8(void);
extern void ScriptCmd_ResetAndDispatch_020be53c(void);
extern void ScriptCmd_ResetScreenLayer_020be0c4(void);
extern void ScriptCmd_SetCursorOverride_020be7d4(void);
extern void ScriptCmd_SetEntityMotion_020be5d4(void);
extern void ScriptCmd_ShowJoinedMessage_020be1e0(void);
extern void ScriptCmd_ShowMessageWindow_020be264(void);
extern void ScriptCmd_StartBrightnessFade_020be62c(void);
extern void ScriptCmd_StartMosaicTransition_020be794(void);
extern void ScriptCmd_WaitScreenLayerIdle_020be0ac(void);
extern void ScriptCmd_WaitScreenLayerIdle_020be0f8(void);
extern void ScriptCmd_WaitWindowAnswer_020be468(void);
extern void ScriptCmd_WaitWindowChoice_020be030(void);
extern void func_ov036_020bdcf0(void);
extern void func_ov036_020bdd30(void);
extern void func_ov036_020bdd64(void);
extern void func_ov036_020be088(void);
extern void func_ov036_020be12c(void);
extern void func_ov036_020be150(void);
extern void func_ov036_020be1a0(void);
extern void func_ov036_020be324(void);
extern void func_ov036_020be3ac(void);
extern void func_ov036_020be4cc(void);
extern void func_ov036_020be608(void);
extern void func_ov036_020be65c(void);

void (*data_ov036_020c373c[64])(void) = {
    ScriptCmd_ResetAndDispatch_020bdcc8,
    PXI_Init_020bdce8,
    func_ov036_020bdcf0,
    NULL,
    func_ov036_020bdd30,
    NULL,
    ScriptCmd_EnterPhase_020bdd54,
    NULL,
    func_ov036_020bdd64,
    IsSceneState0_020bdd94,
    ScriptCmd_OpenActorTextWindow_020bde08,
    NULL,
    ScriptCmd_OpenTextWindowAtCursor_020bdecc,
    NULL,
    ScriptCmd_OpenWindowAtPoint_020bdf88,
    NULL,
    ScriptCmd_WaitWindowChoice_020be030,
    NULL,
    FS_UnloadOverlayImage_020be078,
    DefaultStepDone_020be084,
    func_ov036_020be088,
    ScriptCmd_WaitScreenLayerIdle_020be0ac,
    ScriptCmd_ResetScreenLayer_020be0c4,
    ScriptCmd_WaitScreenLayerIdle_020be0f8,
    IsPxiResourceReadyOrInitialize_020be110,
    NULL,
    func_ov036_020be12c,
    NULL,
    func_ov036_020be150,
    NULL,
    ScriptCmd_EnterPhase_020be190,
    NULL,
    func_ov036_020be1a0,
    NULL,
    ScriptCmd_ShowJoinedMessage_020be1e0,
    NULL,
    ScriptCmd_ShowMessageWindow_020be264,
    NULL,
    func_ov036_020be324,
    NULL,
    func_ov036_020be3ac,
    ScriptCmd_WaitWindowAnswer_020be468,
    func_ov036_020be4cc,
    NULL,
    ScriptCmd_ResetAndDispatch_020be53c,
    PXI_Init_020be55c,
    ScriptCmd_PlaceEntityAndMove_020be564,
    NULL,
    ScriptCmd_SetEntityMotion_020be5d4,
    NULL,
    func_ov036_020be608,
    NULL,
    ScriptCmd_StartBrightnessFade_020be62c,
    NULL,
    func_ov036_020be65c,
    NULL,
    ScriptCmd_OpenFormattedTextWindow_020be69c,
    NULL,
    FSi_CloseFileCommand_020be76c,
    IsResourceReadyOrInitialize_020be770,
    ScriptCmd_StartMosaicTransition_020be794,
    IsSceneState0_020be7c0,
    ScriptCmd_SetCursorOverride_020be7d4,
    NULL,
};
