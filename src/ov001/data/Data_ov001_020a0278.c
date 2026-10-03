#include "nitro/types.h"

extern void AllocateActorSlotOrReportError_02093ae0(void);
extern void FSi_CloseFileCommand_020935dc(void);
extern void FinishStageEventStep_02093a04(void);
extern void NotifyActorGroupAndTarget_02093ac8(void);
extern void RunGateFadeSequence_02093b8c(void);
extern void RunLeaderScriptSlotCommand_0209387c(void);
extern void StartGroupStageScript_020935e0(void);
extern void StartStageActorScript_02093970(void);
extern void UpdateProximityTrigger_02093660(void);
extern void WaitStageActorScript_020938d4(void);
extern void func_ov001_02093afc(void);

void (*data_ov001_020a0278[12])(void) = {
    NULL,
    FSi_CloseFileCommand_020935dc,
    StartGroupStageScript_020935e0,
    UpdateProximityTrigger_02093660,
    RunLeaderScriptSlotCommand_0209387c,
    WaitStageActorScript_020938d4,
    StartStageActorScript_02093970,
    FinishStageEventStep_02093a04,
    NotifyActorGroupAndTarget_02093ac8,
    AllocateActorSlotOrReportError_02093ae0,
    func_ov001_02093afc,
    RunGateFadeSequence_02093b8c,
};
