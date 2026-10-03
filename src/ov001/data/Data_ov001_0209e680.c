#include "nitro/types.h"

extern void EnterPendingRoom_02061e54(void);
extern void ExitSessionAndCommitSave_02062838(void);
extern void HandleMenuPromptResult_020623e8(void);
extern void HandleSessionScriptResult_0206269c(void);
extern void LeaveFieldMenu_02061fc0(void);
extern void RestoreSavedPlacement_02061c6c(void);
extern void SelectNextSessionState_02062150(void);
extern void StepSessionScriptOrAbort_020625b8(void);
extern void StepSessionScriptState_02061f64(void);
extern void WaitSessionPollAndClearFlags_020623b0(void);
extern void WaitSessionPollCallback_02062674(void);
extern void func_ov001_0206257c(void);
extern void func_ov001_02062654(void);

void (*data_ov001_0209e680[13])(void) = {
    RestoreSavedPlacement_02061c6c,
    EnterPendingRoom_02061e54,
    StepSessionScriptState_02061f64,
    LeaveFieldMenu_02061fc0,
    SelectNextSessionState_02062150,
    WaitSessionPollAndClearFlags_020623b0,
    HandleMenuPromptResult_020623e8,
    func_ov001_0206257c,
    StepSessionScriptOrAbort_020625b8,
    func_ov001_02062654,
    WaitSessionPollCallback_02062674,
    HandleSessionScriptResult_0206269c,
    ExitSessionAndCommitSave_02062838,
};
