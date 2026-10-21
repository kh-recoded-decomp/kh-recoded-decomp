#include "nitro/types.h"

extern void func_ov041_020c6b98(void);
extern void func_ov041_020c7264(void);
extern void func_ov041_020c7c34(void);
extern void func_ov041_020c8910(void);
extern void func_ov041_020c8f48(void);
extern void func_ov041_020c948c(void);
extern void func_ov041_020ca02c(void);
extern void EntryActionRevive(void);
extern void EntryActionHeal(void);
extern void EntryActionOnSelf(void);
extern void func_ov041_020ca8fc(void);
extern void func_ov041_020cbcf0(void);
extern void func_ov041_020cc2b8(void);
extern void func_ov041_020cc5e4(void);
extern void func_ov041_020cca68(void);
extern void func_ov041_020ccfc0(void);
extern void func_ov041_020cd7ec(void);
extern void StageEntryStateEnter(void);
extern void func_ov041_020c56c0(void);
extern void StageEntryStateTurn(void);
extern void EntryStateNoop5(void);
extern void func_ov041_020c5c6c(void);
extern void func_ov041_020c631c(void);
extern void EntryStateNoop8(void);
extern void func_ov041_020c6418(void);
extern void StageEntryStateAdvance(void);
extern void StageEntryStateAppear(void);
extern void func_ov041_020c6740(void);
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
    func_ov041_020ca02c,
    EntryActionRevive,
    EntryActionHeal,
    EntryActionOnSelf,
    func_ov041_020ca8fc,
    func_ov041_020cbcf0,
    func_ov041_020cc2b8,
    func_ov041_020cc5e4,
    func_ov041_020cca68,
    func_ov041_020ccfc0,
    func_ov041_020cd7ec,
};

void (*gStageEntryStateHandlers[15])(void) = {
    StageEntryStateEnter,
    func_ov041_020c56c0,
    func_ov041_020c56c0,
    StageEntryStateTurn,
    NULL,
    EntryStateNoop5,
    func_ov041_020c5c6c,
    func_ov041_020c631c,
    EntryStateNoop8,
    func_ov041_020c6418,
    StageEntryStateAdvance,
    StageEntryStateAppear,
    func_ov041_020c6740,
    StageEntryStateRevived,
    StageEntryStateHealed,
};
