#include "nitro/types.h"
#include "src/overlays/ov001/StageManagerFlags.h"

extern void StageEventState_Idle(void); /* Zero retains the current handler state. */
extern void StartGroupStageScript(void); /* StartGroupStageScript */
extern void UpdateProximityTrigger(void); /* UpdateProximityTrigger */
extern void RunLeaderScriptSlotCommand(void); /* RunLeaderScriptSlotCommand */
extern void WaitStageActorScript(void); /* WaitStageActorScript */
extern void StartStageActorScript(void); /* StartStageActorScript */
extern void FinishStageEventStep(void); /* FinishStageEventStep */
extern void NotifyActorGroupAndTarget(void); /* NotifyActorGroupAndTarget */
extern void FinishActorEventStep(void);
extern void RunGateFadeSequence(void); /* RunGateFadeSequence */

void (*gStageScriptStateHandlers[12])(void) = {
    NULL,
    StageEventState_Idle, /* No state transition. */
    StartGroupStageScript, /* StartGroupStageScript */
    UpdateProximityTrigger, /* UpdateProximityTrigger */
    RunLeaderScriptSlotCommand, /* RunLeaderScriptSlotCommand */
    WaitStageActorScript, /* WaitStageActorScript */
    StartStageActorScript, /* StartStageActorScript */
    FinishStageEventStep, /* FinishStageEventStep */
    NotifyActorGroupAndTarget, /* NotifyActorGroupAndTarget */
    /* Legacy table erases return types; keep the real int prototype above. */
    (void (*)(void))ClearStageMask30WhenBit0Clear,
    FinishActorEventStep,
    RunGateFadeSequence, /* RunGateFadeSequence */
};
