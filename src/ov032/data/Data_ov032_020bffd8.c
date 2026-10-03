#include "nitro/types.h"

extern void AcknowledgeGroupTransition_020ba940(void);
extern void AdvanceToRoutedSlot_020bb014(void);
extern void ClearGroupTransitionFlags_020bb330(void);
extern void CommitGroupActionState_020bb1c8(void);
extern void CompleteGroupTransition_020baad0(void);
extern void EnterGroupActionState_020bb1f8(void);
extern void EnterState12WithHalfRate_020bb1ac(void);
extern void FinishGroupActionState_020bb25c(void);
extern void FinishGroupTransition_020bb150(void);
extern void FinishMovieMenuLoad_020ba984(void);
extern void InitializeGroupAction_020bb12c(void);
extern void LoadShadowAndFlagScene_020ba90c(void);
extern void ResumeSceneAndAdvance_020baa08(void);
extern void SetSlotDisplayStyle_020ba8a0(void);
extern void TryOpenGroupAction_020bb220(void);
extern void func_ov032_020ba96c(void);
extern void func_ov032_020bab04(void);
extern void func_ov032_020bb284(void);

void (*data_ov032_020bffd8[18])(void) = {
    SetSlotDisplayStyle_020ba8a0,
    LoadShadowAndFlagScene_020ba90c,
    AcknowledgeGroupTransition_020ba940,
    func_ov032_020ba96c,
    FinishMovieMenuLoad_020ba984,
    ResumeSceneAndAdvance_020baa08,
    CompleteGroupTransition_020baad0,
    func_ov032_020bab04,
    AdvanceToRoutedSlot_020bb014,
    InitializeGroupAction_020bb12c,
    FinishGroupTransition_020bb150,
    EnterState12WithHalfRate_020bb1ac,
    CommitGroupActionState_020bb1c8,
    EnterGroupActionState_020bb1f8,
    TryOpenGroupAction_020bb220,
    FinishGroupActionState_020bb25c,
    func_ov032_020bb284,
    ClearGroupTransitionFlags_020bb330,
};
