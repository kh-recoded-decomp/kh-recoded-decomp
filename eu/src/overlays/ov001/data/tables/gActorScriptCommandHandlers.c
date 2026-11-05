#include "nitro/types.h"

extern void ScriptCmd_SetScreenSwap(void); /* ScriptCmd_SetScreenSwap */
extern void ScriptCmd_ActorNop01(void); /* DefaultStepDone */
extern void ScriptCmd_PushActorVramState(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_ReleaseSceneActors(void); /* ScriptCmd_ReleaseSceneActors */
extern void ScriptOp_RunActorPass(void); /* ScriptOp_RunActorPass */
extern void ScriptCmd_BeginBrightnessFade(void); /* ScriptCmd_BeginBrightnessFade */
extern void ScriptCmd_UpdateScreenBrightnessFades(void); /* ScriptCmd_UpdateScreenBrightnessFades */
extern void ScriptCmd_ActorNop06(void); /* DefaultStepDone */
extern void ScriptResume_ActorNop06(void); /* DefaultStepDone */
extern void ScriptCmd_InitActorCollision(void); /* ScriptCmd_InitActorCollision */
extern void ScriptCmd_PlaceActor(void); /* ScriptCmd_PlaceActor */
extern void ScriptCmd_DetachActorAnimation(void); /* ScriptCmd_DetachActorAnimation */
extern void ScriptCmd_PlayActorUnnamedMotion(void); /* ScriptCmd_PlayActorUnnamedMotion */
extern void ScriptCmd_AttachActorToParent(void); /* ScriptCmd_AttachActorToParent */
extern void Script_ApplyActorAnimationState(void); /* Script_ApplyActorAnimationState */
extern void ScriptCmd_AttachActorObject(void); /* ScriptCmd_AttachActorObject */
extern void ScriptCmd_ShowActor(void); /* ScriptCmd_ShowActor */
extern void ScriptCmd_HideActor(void); /* ScriptCmd_HideActor */
extern void ScriptCmd_SetActorProbeSphere(void); /* ScriptCmd_SetActorProbeSphere */
extern void updateActorTransitionParameterRampCommand_0208cb3c(void); /* updateActorTransitionParameterRampCommand */
extern void ScriptCmd_DisableResolvedActorProbeSphere(void);
extern void Script_MakeActorTranslucentAndClearVerticalOffset_0208ded8(void); /* Script_MakeActorTranslucentAndClearVerticalOffset */
extern void PlaceActorRelativeToActor(void); /* PlaceActorRelativeToActor */
extern void Script_SetActorParameterFromInteger(void); /* Script_SetActorParameterFromInteger */
extern void ScriptCmd_PlaceActor_0208e114(void); /* ScriptCmd_PlaceActor */
extern void ScriptCmd_BindActorTarget(void); /* ScriptCmd_BindActorTarget */
extern void ScriptCmd_SetElemFieldIfFlagSet(void); /* ScriptCmd_SetElemFieldIfFlagSet */
extern void ScriptCmd_SetActorPlaybackRate(void); /* ScriptCmd_SetActorPlaybackRate */
extern void ScriptCmd_SetActorFlagBit4(void); /* ScriptCmd_SetActorFlagBit4 */
extern void ScriptCmd_SetActorPrimarySlot(void); /* ScriptCmd_SetActorPrimarySlot */
extern void ScriptCmd_SetActorAlpha(void); /* ScriptCmd_SetActorAlpha */
extern void ScriptCmd_UpdateActorAlphaFade(void); /* ScriptCmd_UpdateActorAlphaFade */
extern void ScriptCmd_StartActorRotation(void); /* ScriptCmd_StartActorRotation */
extern void ScriptCmd_ActorNop1C(void); /* DefaultStepDone */
extern void ScriptCmd_ActorNop1D(void); /* DefaultStepDone */
extern void ScriptCmd_PlayActorMotionOrBlend(void); /* ScriptCmd_PlayActorMotionOrBlend */
extern void ScriptCmd_StoreIfFree_0208cda8(void); /* ScriptCmd_StoreIfFree */
extern void ScriptCmd_TestActorSlotMaskBit(void); /* ScriptCmd_TestActorSlotMaskBit */
extern void ScriptCmd_PlayActorMotion(void); /* ScriptCmd_PlayActorMotion */
extern void Script_SetActorAnimationFrame_0208df2c(void); /* Script_SetActorAnimationFrame */
extern void ScriptCmd_SetActorMoveTarget(void); /* ScriptCmd_SetActorMoveTarget */
extern void ScriptCmd_WaitActorReady(void); /* ScriptCmd_WaitActorReady */
extern void ScriptCmd_SetActorHeadingTowardTarget(void); /* ScriptCmd_SetActorHeadingTowardTarget */
extern void ScriptCmd_SetActorHeadingDegrees(void); /* ScriptCmd_SetActorHeadingDegrees */
extern void ScriptCmd_StartChannelTransform(void); /* ScriptCmd_StartChannelTransform */
extern void ScriptCmd_SetActorChannelState(void); /* ScriptCmd_SetActorChannelState */
extern void ScriptCmd_PlayActorChannel(void); /* ScriptCmd_PlayActorChannel */
extern void ScriptCmd_WaitForFieldCameraTransition(void); /* thumbStep */
extern void ScriptCmd_ResetFieldCameraChannel(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_RestoreSavedFieldCamera(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_SetCameraTarget(void); /* ScriptCmd_SetCameraTarget */
extern void ScriptCmd_ActorTimerOrAnim(void); /* ScriptCmd_ActorTimerOrAnim */
extern void ScriptCmd_ClearActorTimers(void); /* ScriptCmd_ClearActorTimers */
extern void ScriptCmd_ActorNop2F(void); /* DefaultStepDone */
extern void ScriptCmd_ActorNop30(void); /* DefaultStepDone */
extern void ScriptCmd_PlaySoundAtActor(void); /* ScriptCmd_PlaySoundAtActor */
extern void ScriptCmd_ShowActorMessage(void); /* ScriptCmd_ShowActorMessage */
extern void ScriptCmd_ShowPendingActorDialogText(void);
extern void ScriptCmd_ResetAndSetElemField(void); /* ScriptCmd_ResetAndSetElemField */
extern void ScriptCmd_SetElemFieldAndDispatch(void); /* ScriptCmd_SetElemFieldAndDispatch */
extern void ScriptCmd_SetEntityFlag(void); /* ScriptCmd_SetEntityFlag */
extern void ScriptCmd_StartScreenOverlayFade(void); /* ScriptCmd_StartScreenOverlayFade */
extern void ScriptCmd_UpdateScreenOverlayFade(void); /* ScriptCmd_UpdateScreenOverlayFade */
extern void ScriptCmd_PlayActorNamedMotion(void); /* ScriptCmd_PlayActorNamedMotion */
extern void ScriptCmd_ShowSpeakerMessage(void); /* ScriptCmd_ShowSpeakerMessage */
extern void ScriptCmd_ShowTwoChoiceMessage(void); /* ScriptCmd_ShowTwoChoiceMessage */
extern void ScriptCmd_ShowMessageWindow(void); /* ScriptCmd_ShowMessageWindow */
extern void ScriptCmd_ActorNop3B(void); /* DefaultStepDone */
extern void ScriptCmd_DispatchToHandler(void);
extern void ScriptCmd_StartScreenFade(void); /* ScriptCmd_StartScreenFade */
extern void IsResourceReadyOrInitialize(void); /* IsResourceReadyOrInitialize */
extern void ScriptCmd_OpenFieldPanelScreen(void); /* ScriptCmd_OpenFieldPanelScreen */
extern void ScriptCmd_CloseFieldPanelScreen(void); /* ScriptCmd_CloseFieldPanelScreen */
extern void ScriptCmd_SetActorExtraAnimation(void); /* ScriptCmd_SetActorExtraAnimation */
extern void ScriptCmd_SetActorExtraSlot(void); /* ScriptCmd_SetActorExtraSlot */
extern void ScriptCmd_MoveActorToPosition(void); /* ScriptCmd_MoveActorToPosition */
extern void ScriptCmd_SetSubScreenVisible(void); /* ScriptCmd_SetSubScreenVisible */
extern void ScriptCmd_SetActorSecondarySlot(void); /* ScriptCmd_SetActorSecondarySlot */
extern void ScriptCmd_TurnActorToHeading(void); /* ScriptCmd_TurnActorToHeading */
extern void ScriptCmd_TurnActorTowardTarget(void); /* ScriptCmd_TurnActorTowardTarget */
extern void ScriptCmd_IsActorHeadingReached(void); /* ScriptCmd_IsActorHeadingReached */
extern void ScriptCmd_SetWorkString(void); /* ScriptCmd_SetWorkString */
extern void FreeScriptWorkBuffers(void); /* FreeScriptWorkBuffers */
extern void ScriptCmd_ActorNop4A(void); /* DefaultStepDone */
extern void ScriptResume_ActorNop4A(void); /* DefaultStepDone */
extern void PickRandomUnsetSessionFlag(void); /* PickRandomUnsetSessionFlag */
extern void ScriptCmd_BeginEventCameraAndFreezeSubMode(void);
extern void ScriptCmd_FinishEventCameraAndUnfreezeSubMode(void);
extern void ScriptCmd_ShowItemMessage(void); /* ScriptCmd_ShowItemMessage */
extern void ScriptCmd_PlayStageEventAnimation(void); /* ScriptCmd_PlayStageEventAnimation */
extern void ScriptCmd_GrantRecordPair(void);
extern void ScriptCmd_SetSceneFlagBit2(void);
extern void ScriptCmd_FaceTargetWithAnims(void); /* ScriptCmd_FaceTargetWithAnims */
extern void ScriptOp_InitSubsystemIfFlagClear(void); /* ScriptOp_InitSubsystemIfFlagClear */
extern void ScriptCmd_QueueCameraAngleTransition(void); /* ScriptCmd_QueueCameraAngleTransition */
extern void ScriptCmd_FrameCameraOnActor(void); /* ScriptCmd_EnterPhase */
extern void ScriptCmd_SetActorAngleDegrees(void);
extern void RefreshPartyMemberStates(void); /* RefreshPartyMemberStates */
extern void RecordPlayerStateFlags(void); /* RecordPlayerStateFlags */
extern void Actor_BroadcastCallback(void); /* Actor_BroadcastCallback */
extern void ScriptCmd_WaitMenuState(void); /* ScriptCmd_WaitMenuState */
extern void ScriptCmd_RefreshFieldHudIconRecords(void); /* FS_UnloadOverlayImage */
extern void ScriptCmd_TryStartPanelListScroll(void); /* thumbStep */

void (*gActorScriptCommandHandlers[186])(void) = {
    ScriptCmd_SetScreenSwap, /* ScriptCmd_SetScreenSwap */
    NULL,
    ScriptCmd_ActorNop01, /* DefaultStepDone */
    NULL,
    ScriptCmd_PushActorVramState, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_ReleaseSceneActors, /* ScriptCmd_ReleaseSceneActors */
    NULL,
    ScriptOp_RunActorPass, /* ScriptOp_RunActorPass */
    NULL,
    ScriptCmd_BeginBrightnessFade, /* ScriptCmd_BeginBrightnessFade */
    ScriptCmd_UpdateScreenBrightnessFades, /* ScriptCmd_UpdateScreenBrightnessFades */
    ScriptCmd_ActorNop06, /* DefaultStepDone */
    ScriptResume_ActorNop06, /* DefaultStepDone */
    ScriptCmd_InitActorCollision, /* ScriptCmd_InitActorCollision */
    NULL,
    ScriptCmd_PlaceActor, /* ScriptCmd_PlaceActor */
    NULL,
    ScriptCmd_DetachActorAnimation, /* ScriptCmd_DetachActorAnimation */
    NULL,
    ScriptCmd_PlayActorUnnamedMotion, /* ScriptCmd_PlayActorUnnamedMotion */
    NULL,
    ScriptCmd_AttachActorToParent, /* ScriptCmd_AttachActorToParent */
    NULL,
    Script_ApplyActorAnimationState, /* Script_ApplyActorAnimationState */
    NULL,
    ScriptCmd_AttachActorObject, /* ScriptCmd_AttachActorObject */
    NULL,
    ScriptCmd_ShowActor, /* ScriptCmd_ShowActor */
    NULL,
    ScriptCmd_HideActor, /* ScriptCmd_HideActor */
    NULL,
    ScriptCmd_SetActorProbeSphere, /* ScriptCmd_SetActorProbeSphere */
    updateActorTransitionParameterRampCommand_0208cb3c, /* updateActorTransitionParameterRampCommand */
    ScriptCmd_DisableResolvedActorProbeSphere,
    NULL,
    Script_MakeActorTranslucentAndClearVerticalOffset_0208ded8, /* Script_MakeActorTranslucentAndClearVerticalOffset */
    NULL,
    PlaceActorRelativeToActor, /* PlaceActorRelativeToActor */
    NULL,
    Script_SetActorParameterFromInteger, /* Script_SetActorParameterFromInteger */
    NULL,
    ScriptCmd_PlaceActor_0208e114, /* ScriptCmd_PlaceActor */
    NULL,
    ScriptCmd_BindActorTarget, /* ScriptCmd_BindActorTarget */
    ScriptCmd_SetElemFieldIfFlagSet, /* ScriptCmd_SetElemFieldIfFlagSet */
    ScriptCmd_SetActorPlaybackRate, /* ScriptCmd_SetActorPlaybackRate */
    NULL,
    ScriptCmd_SetActorFlagBit4, /* ScriptCmd_SetActorFlagBit4 */
    NULL,
    ScriptCmd_SetActorPrimarySlot, /* ScriptCmd_SetActorPrimarySlot */
    NULL,
    ScriptCmd_SetActorAlpha, /* ScriptCmd_SetActorAlpha */
    ScriptCmd_UpdateActorAlphaFade, /* ScriptCmd_UpdateActorAlphaFade */
    ScriptCmd_StartActorRotation, /* ScriptCmd_StartActorRotation */
    NULL,
    ScriptCmd_ActorNop1C, /* DefaultStepDone */
    NULL,
    ScriptCmd_ActorNop1D, /* DefaultStepDone */
    NULL,
    ScriptCmd_PlayActorMotionOrBlend, /* ScriptCmd_PlayActorMotionOrBlend */
    NULL,
    ScriptCmd_StoreIfFree_0208cda8, /* ScriptCmd_StoreIfFree */
    ScriptCmd_TestActorSlotMaskBit, /* ScriptCmd_TestActorSlotMaskBit */
    ScriptCmd_PlayActorMotion, /* ScriptCmd_PlayActorMotion */
    NULL,
    Script_SetActorAnimationFrame_0208df2c, /* Script_SetActorAnimationFrame */
    NULL,
    ScriptCmd_SetActorMoveTarget, /* ScriptCmd_SetActorMoveTarget */
    NULL,
    ScriptCmd_WaitActorReady, /* ScriptCmd_WaitActorReady */
    NULL,
    ScriptCmd_SetActorHeadingTowardTarget, /* ScriptCmd_SetActorHeadingTowardTarget */
    NULL,
    ScriptCmd_SetActorHeadingDegrees, /* ScriptCmd_SetActorHeadingDegrees */
    NULL,
    ScriptCmd_StartChannelTransform, /* ScriptCmd_StartChannelTransform */
    NULL,
    ScriptCmd_SetActorChannelState, /* ScriptCmd_SetActorChannelState */
    NULL,
    ScriptCmd_PlayActorChannel, /* ScriptCmd_PlayActorChannel */
    NULL,
    ScriptCmd_WaitForFieldCameraTransition, /* thumbStep */
    NULL,
    ScriptCmd_ResetFieldCameraChannel, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_RestoreSavedFieldCamera, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_SetCameraTarget, /* ScriptCmd_SetCameraTarget */
    NULL,
    ScriptCmd_ActorTimerOrAnim, /* ScriptCmd_ActorTimerOrAnim */
    NULL,
    ScriptCmd_ClearActorTimers, /* ScriptCmd_ClearActorTimers */
    NULL,
    ScriptCmd_ActorNop2F, /* DefaultStepDone */
    NULL,
    ScriptCmd_ActorNop30, /* DefaultStepDone */
    NULL,
    ScriptCmd_PlaySoundAtActor, /* ScriptCmd_PlaySoundAtActor */
    NULL,
    ScriptCmd_ShowActorMessage, /* ScriptCmd_ShowActorMessage */
    NULL,
    ScriptCmd_ShowPendingActorDialogText,
    NULL,
    ScriptCmd_ResetAndSetElemField, /* ScriptCmd_ResetAndSetElemField */
    ScriptCmd_SetElemFieldAndDispatch, /* ScriptCmd_SetElemFieldAndDispatch */
    ScriptCmd_SetEntityFlag, /* ScriptCmd_SetEntityFlag */
    NULL,
    ScriptCmd_StartScreenOverlayFade, /* ScriptCmd_StartScreenOverlayFade */
    ScriptCmd_UpdateScreenOverlayFade, /* ScriptCmd_UpdateScreenOverlayFade */
    ScriptCmd_PlayActorNamedMotion, /* ScriptCmd_PlayActorNamedMotion */
    NULL,
    ScriptCmd_ShowSpeakerMessage, /* ScriptCmd_ShowSpeakerMessage */
    NULL,
    ScriptCmd_ShowTwoChoiceMessage, /* ScriptCmd_ShowTwoChoiceMessage */
    NULL,
    ScriptCmd_ShowMessageWindow, /* ScriptCmd_ShowMessageWindow */
    NULL,
    ScriptCmd_ActorNop3B, /* DefaultStepDone */
    NULL,
    ScriptCmd_DispatchToHandler,
    NULL,
    ScriptCmd_StartScreenFade, /* ScriptCmd_StartScreenFade */
    IsResourceReadyOrInitialize, /* IsResourceReadyOrInitialize */
    ScriptCmd_OpenFieldPanelScreen, /* ScriptCmd_OpenFieldPanelScreen */
    NULL,
    ScriptCmd_CloseFieldPanelScreen, /* ScriptCmd_CloseFieldPanelScreen */
    NULL,
    ScriptCmd_SetActorExtraAnimation, /* ScriptCmd_SetActorExtraAnimation */
    NULL,
    ScriptCmd_SetActorExtraSlot, /* ScriptCmd_SetActorExtraSlot */
    NULL,
    ScriptCmd_MoveActorToPosition, /* ScriptCmd_MoveActorToPosition */
    NULL,
    ScriptCmd_SetSubScreenVisible, /* ScriptCmd_SetSubScreenVisible */
    NULL,
    ScriptCmd_SetActorSecondarySlot, /* ScriptCmd_SetActorSecondarySlot */
    NULL,
    ScriptCmd_TurnActorToHeading, /* ScriptCmd_TurnActorToHeading */
    NULL,
    ScriptCmd_TurnActorTowardTarget, /* ScriptCmd_TurnActorTowardTarget */
    NULL,
    ScriptCmd_IsActorHeadingReached, /* ScriptCmd_IsActorHeadingReached */
    NULL,
    ScriptCmd_SetWorkString, /* ScriptCmd_SetWorkString */
    NULL,
    FreeScriptWorkBuffers, /* FreeScriptWorkBuffers */
    NULL,
    ScriptCmd_ActorNop4A, /* DefaultStepDone */
    ScriptResume_ActorNop4A, /* DefaultStepDone */
    PickRandomUnsetSessionFlag, /* PickRandomUnsetSessionFlag */
    NULL,
    ScriptCmd_BeginEventCameraAndFreezeSubMode,
    NULL,
    ScriptCmd_FinishEventCameraAndUnfreezeSubMode,
    NULL,
    ScriptCmd_ShowItemMessage, /* ScriptCmd_ShowItemMessage */
    NULL,
    ScriptCmd_PlayStageEventAnimation, /* ScriptCmd_PlayStageEventAnimation */
    NULL,
    ScriptCmd_GrantRecordPair,
    NULL,
    ScriptCmd_SetSceneFlagBit2,
    NULL,
    ScriptCmd_FaceTargetWithAnims, /* ScriptCmd_FaceTargetWithAnims */
    NULL,
    ScriptOp_InitSubsystemIfFlagClear, /* ScriptOp_InitSubsystemIfFlagClear */
    NULL,
    ScriptCmd_QueueCameraAngleTransition, /* ScriptCmd_QueueCameraAngleTransition */
    NULL,
    ScriptCmd_FrameCameraOnActor, /* ScriptCmd_EnterPhase */
    NULL,
    ScriptCmd_SetActorAngleDegrees,
    NULL,
    RefreshPartyMemberStates, /* RefreshPartyMemberStates */
    NULL,
    RecordPlayerStateFlags, /* RecordPlayerStateFlags */
    NULL,
    Actor_BroadcastCallback, /* Actor_BroadcastCallback */
    NULL,
    ScriptCmd_WaitMenuState, /* ScriptCmd_WaitMenuState */
    NULL,
    ScriptCmd_RefreshFieldHudIconRecords, /* FS_UnloadOverlayImage */
    NULL,
    ScriptCmd_TryStartPanelListScroll, /* thumbStep */
    NULL,
};
