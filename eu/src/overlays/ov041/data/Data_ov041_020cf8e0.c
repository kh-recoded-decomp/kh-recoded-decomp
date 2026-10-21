#include "nitro/types.h"

extern void StageStateSetupSlots(void);
extern void StageStateStartMusic(void);
extern void StageStateStartSubMode(void);
extern void StageStateFadeBgm(void);
extern void StageStateWaitScreenIdle(void);
extern void StageStateIntro(void);
extern void func_ov041_020bf924(void);
extern void func_ov041_020bfbe0(void);
extern void StageStateAfterTurn(void);
extern void StageStatePlayerTurn(void);
extern void StageStateEndTurn(void);
extern void StageStateRunTurn(void);
extern void StageStateChooseTarget(void);
extern void StageStateStartTurn(void);
extern void StageStateChooseItemTarget(void);
extern void StageStateUseItem(void);
extern void StageStateNoop16(void);
extern void StageStateWon(void);
extern void StageStateRunFieldOp428(void);
extern void StageStateRetreat(void);
extern void StageStateFadeOut(void);
extern void StageStateFinish(void);
extern void StageStateNoop22(void);

#pragma explicit_zero_data on

void (*gStageStateHandlers[23])(void) = {
    StageStateSetupSlots,
    StageStateStartMusic,
    StageStateStartSubMode,
    StageStateFadeBgm,
    StageStateWaitScreenIdle,
    StageStateIntro,
    func_ov041_020bf924,
    func_ov041_020bfbe0,
    StageStateAfterTurn,
    StageStatePlayerTurn,
    StageStateEndTurn,
    StageStateRunTurn,
    StageStateChooseTarget,
    StageStateStartTurn,
    StageStateChooseItemTarget,
    StageStateUseItem,
    StageStateNoop16,
    StageStateWon,
    StageStateRunFieldOp428,
    StageStateRetreat,
    StageStateFadeOut,
    StageStateFinish,
    StageStateNoop22,
};
