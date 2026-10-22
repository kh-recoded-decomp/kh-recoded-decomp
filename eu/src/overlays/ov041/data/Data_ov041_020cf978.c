#include "nitro/types.h"

extern void EntryActionCombo(void);
extern void EntryActionRushAttack(void);
extern void EntryActionMagic(void);
extern void EntryActionSpecialCombo(void);
extern void EntryActionDash(void);
extern void func_ov041_020c948c(void);
extern void EntryActionMelee(void);
extern void EntryActionRevive(void);
extern void EntryActionHeal(void);
extern void EntryActionOnSelf(void);
extern void EntryActionCast(void);
extern void EntryActionBarrage(void);
extern void EntryActionSpell(void);
extern void EntryActionPathAttack(void);
extern void EntryActionTeamAttack(void);
extern void EntryActionTeamSlash(void);
extern void EntryActionTeamBlast(void);
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
    EntryActionCombo,
    EntryActionRushAttack,
    EntryActionMagic,
    EntryActionSpecialCombo,
    EntryActionDash,
    func_ov041_020c948c,
    EntryActionMelee,
    EntryActionRevive,
    EntryActionHeal,
    EntryActionOnSelf,
    EntryActionCast,
    EntryActionBarrage,
    EntryActionSpell,
    EntryActionPathAttack,
    EntryActionTeamAttack,
    EntryActionTeamSlash,
    EntryActionTeamBlast,
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
