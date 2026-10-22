#include "nitro/types.h"

extern void func_ov041_020c6b98(void);
extern void func_ov041_020c7264(void);
extern void func_ov041_020c7c34(void);
extern void func_ov041_020c8910(void);
extern void func_ov041_020c8f48(void);
extern void func_ov041_020c948c(void);
extern void EntryActionMelee(void);
extern void EntryActionRevive(void);
extern void EntryActionHeal(void);
extern void EntryActionOnSelf(void);
extern void func_ov041_020ca8fc(void);
extern void func_ov041_020cbcf0(void);
extern void EntryActionSpell(void);
extern void EntryActionPathAttack(void);
extern void EntryActionTeamAttack(void);
extern void func_ov041_020ccfc0(void);
extern void func_ov041_020cd7ec(void);
extern void StageEntryStateEnter(void);
extern void StageEntryStateWaiting(void);
extern void StageEntryStateTurn(void);
extern void EntryStateNoop5(void);
extern void StageEntryStateDefeated(void);
extern void StageEntryStateStepBack(void);
extern void EntryStateNoop8(void);
extern void StageEntryStateStepForward(void);
extern void StageEntryStateAdvance(void);
extern void StageEntryStateAppear(void);
extern void EntryStateStatusCommand(void);
extern void StageEntryStateRevived(void);
extern void StageEntryStateHealed(void);

#pragma explicit_zero_data on

void (*gStageEntryActionHandlers[17])(void) = {
    func_ov041_020c6b98,
    func_ov041_020c7264,
    func_ov041_020c7c34,
    func_ov041_020c8910,
    func_ov041_020c8f48,
    func_ov041_020c948c,
    EntryActionMelee,
    EntryActionRevive,
    EntryActionHeal,
    EntryActionOnSelf,
    func_ov041_020ca8fc,
    func_ov041_020cbcf0,
    EntryActionSpell,
    EntryActionPathAttack,
    EntryActionTeamAttack,
    func_ov041_020ccfc0,
    func_ov041_020cd7ec,
};

void (*gStageEntryStateHandlers[15])(void) = {
    StageEntryStateEnter,
    StageEntryStateWaiting,
    StageEntryStateWaiting,
    StageEntryStateTurn,
    NULL,
    EntryStateNoop5,
    StageEntryStateDefeated,
    StageEntryStateStepBack,
    EntryStateNoop8,
    StageEntryStateStepForward,
    StageEntryStateAdvance,
    StageEntryStateAppear,
    EntryStateStatusCommand,
    StageEntryStateRevived,
    StageEntryStateHealed,
};
