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
extern void func_ov041_020bf5b0(void);
extern void StageStateRunTurn(void);
extern void func_ov041_020bfe84(void);
extern void StageStateStartTurn(void);
extern void func_ov041_020c00a8(void);
extern void func_ov041_020c021c(void);
extern void StageStateNoop16(void);
extern void func_ov041_020c04a0(void);
extern void StageStateRunFieldOp428(void);
extern void StageStateRetreat(void);
extern void StageStateFadeOut(void);
extern void func_ov041_020c07ec(void);
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
    func_ov041_020bf5b0,
    StageStateRunTurn,
    func_ov041_020bfe84,
    StageStateStartTurn,
    func_ov041_020c00a8,
    func_ov041_020c021c,
    StageStateNoop16,
    func_ov041_020c04a0,
    StageStateRunFieldOp428,
    StageStateRetreat,
    StageStateFadeOut,
    func_ov041_020c07ec,
    StageStateNoop22,
};
