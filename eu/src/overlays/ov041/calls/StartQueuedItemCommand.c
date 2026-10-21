#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

#define ITEM_ACTION 2 /* the slot of StageEntry.actions an item's action is copied to */

extern const fx32 data_ov041_020cf568[];
extern const fx32 data_ov041_020cf554[];
extern const fx32 data_ov041_020cf4f0[];
extern const fx32 data_ov041_020cf4b0[];
extern const int data_ov041_020cf4e0[];
extern const int data_ov041_020cf594[][4];
extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern u8 CountActiveStageEntries(BOOL primary);
extern int PickStageTarget(int mode);
extern int PickNearbyTarget(StageEntry *entries);
extern void SetStageEntryState(u8 entryIndex, int state);
extern int func_0202a9e4(u16 range);
extern int GetCommandEffectKind(int commandId);
extern void InvokeFieldModeOp2c4(int commandId);

/*
 * Starts a command taken from the field's queue (items 0xe1-0xec, with a level in arg): loads the item's action
 * (also for the second and third primary entries on group items), scales its power by the level (and by how
 * many entries are still in for items 0xe4-0xe6), picks a target and hands the action to the entries that use
 * it; item 0xec instead draws a random command of its level and starts it as a command.
 */
void StartQueuedItemCommand(StageFieldCommand *command)
{
    StageWork *work = gMovieContextState->stageWork;
    int id = command->id;
    int arg = command->arg;
    int action;
    int i;
    int target;

    switch (id) {
    case 0xe1:
        action = 6;
        break;
    case 0xe2:
        action = 7;
        break;
    case 0xe3:
        action = 8;
        break;
    case 0xe4:
        action = 9;
        break;
    case 0xe5:
        action = 0xc;
        break;
    case 0xe6:
        action = 0xf;
        break;
    case 0xe7:
        action = 0x12;
        break;
    case 0xe8:
        action = 0x13;
        break;
    case 0xe9:
        action = 0x14;
        break;
    case 0xea:
        action = 0x15;
        break;
    case 0xeb:
        action = 0x16;
        break;
    case 0xec:
        action = 0x17;
        break;
    }
    MIi_CpuCopyFast(&work->itemActionTable->actions[action], &work->itemActions[0], sizeof(StageEntryAction));
    work->itemActions[0].effect = id;
    work->itemActions[0].effectArg = arg;
    if (action == 9 || action == 0xc || action == 0xf) {
        if ((work->flags & 0x800) && work->entries[1].state != STAGE_ENTRY_OUT) {
            MIi_CpuCopyFast(&work->itemActionTable->actions[action + 1], &work->itemActions[1], sizeof(StageEntryAction));
        }
        if ((work->flags & 0x400) && work->entries[2].state != STAGE_ENTRY_OUT) {
            MIi_CpuCopyFast(&work->itemActionTable->actions[action + 2], &work->itemActions[2], sizeof(StageEntryAction));
        }
    }
    for (i = 0; i < 3; i++) {
        work->itemActions[i].altEffectCategory = work->itemActions[i].hitEffectCategory;
        work->itemActions[i].altEffectIndex = work->itemActions[i].hitEffectIndex;
        work->itemActions[i].altEffectAnimation = work->itemActions[i].hitEffectAnimation;
    }
    switch (id) {
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe7:
    case 0xe8:
    case 0xe9:
    case 0xea:
        work->itemActions[0].power = FX_Mul(work->itemActions[0].power, data_ov041_020cf568[arg]);
        break;
    case 0xe4:
    case 0xe5:
    case 0xe6:
        work->itemActions[0].power = FX_Mul(work->itemActions[0].power, data_ov041_020cf554[arg]);
        work->itemActions[0].power =
            FX_Mul(work->itemActions[0].power, data_ov041_020cf4f0[CountActiveStageEntries(TRUE) - 1]);
        break;
    case 0xeb:
        work->itemActions[0].power = FX_Mul(work->itemActions[0].power, data_ov041_020cf4b0[arg]);
        break;
    case 0xec:
        break;
    }
    target = -1;
    switch (work->itemActions[0].targetKind) {
    case 0:
    case 1:
        target = PickStageTarget(work->itemActions[0].targetKind);
        break;
    case 4:
        target = PickNearbyTarget(work->entries);
        break;
    case 9:
        break;
    }
    switch (work->itemActions[0].effect) {
    case 0xe4:
    case 0xe5:
    case 0xe6:
        for (i = 0; i < work->primaryCount; i++) {
            if (work->entries[i].state != STAGE_ENTRY_OUT) {
                SetStageEntryState(i, 4);
                work->entries[i].actions[ITEM_ACTION] = work->itemActions[i];
                work->entries[i].actionIndex = ITEM_ACTION;
                work->entries[i].mainTarget = target;
            }
        }
        break;
    case 0xec:
        work->commandId = data_ov041_020cf594[arg][func_0202a9e4(data_ov041_020cf4e0[arg] * 1000) / 1000];
        work->commandEffectKind = GetCommandEffectKind(work->commandId);
        switch (work->commandEffectKind) {
        case 7:
        case 8:
            work->commandEffectKind = 8;
        case 9:
            work->targetIndex = 0;
            break;
        }
        SetStageEntryState(0, 0xc);
        InvokeFieldModeOp2c4(work->commandId);
        if (work->commandId == 0xcb) {
            work->flags |= STAGE_WORK_STOP_COMMANDS;
        }
        break;
    case 0xeb:
        SetStageEntryState(0, 4);
        work->entries[0].actions[ITEM_ACTION] = work->itemActions[0];
        work->entries[0].actionIndex = ITEM_ACTION;
        work->entries[0].mainTarget = 0;
        work->entries[0].actions[ITEM_ACTION].targetKind = 8;
        break;
    default:
        SetStageEntryState(0, 4);
        work->entries[0].actions[ITEM_ACTION] = work->itemActions[0];
        work->entries[0].actionIndex = ITEM_ACTION;
        work->entries[0].mainTarget = target;
        break;
    }
}
