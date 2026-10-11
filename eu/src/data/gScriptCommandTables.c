#include "src/calls/ScriptCommandTables.h"

#pragma explicit_zero_data on

extern int ScriptCmd_CopyOperandOrInvokeHandler(ScriptVm *, u8 *);
extern int ScriptCmd_SetElemOffset(ScriptVm *, u8 *);
extern int FSi_CloseFileCommandNoOpA(ScriptVm *, u8 *);
extern int ByteCode_ExecuteLoadOp(ScriptVm *, s32);
extern int FSi_EmptyArchiveProcThumbStub(ScriptVm *, u8 *);
extern int ResetRequestRecord(ScriptVm *, u8 *);
extern int ScriptCmd_AdvanceElemCursor(ScriptVm *, u8 *);
extern int ScriptVm_RunCallback(ScriptVm *, u8 *);
extern int IsDerefZero(ScriptVm *, s32);
extern int FSi_CloseFileCommandNoOpB(ScriptVm *, u8 *);
extern int FSi_CloseFileCommandNoOpC(ScriptVm *, s32);
extern int ScriptCmd_SetBranchTarget(ScriptVm *, u8 *);
extern int ScriptCmd_SetElemFieldFromOperand(ScriptVm *, u8 *);
extern int ScriptCmd_AdvanceOrSetField(ScriptVm *, s32);
extern int ScriptCmd_ArmPair(ScriptVm *, u8 *);
extern int func_02026590(ScriptVm *, u8 *);
extern int func_020265ec(ScriptVm *, u8 *);
extern int func_02026634(ScriptVm *, u8 *);
extern int func_02026678(ScriptVm *, u8 *);
extern int func_020266d0(ScriptVm *, u8 *);
extern int func_02026704(ScriptVm *, s32);
extern int ScriptCmd_QueueSoundKind1(ScriptVm *, u8 *);
extern int Script_StepAndIsIdle(ScriptVm *, s32);
extern int func_02026754(ScriptVm *, u8 *);
extern int func_02026788(ScriptVm *, u8 *);
extern int func_020267b8(ScriptVm *, u8 *);
extern int func_020267d8(ScriptVm *, u8 *);
extern int ScriptCmd_LoadFileToSlot(ScriptVm *, u8 *);
extern int ScriptCmd_FreeFileSlot(ScriptVm *, u8 *);
extern int ScriptCmd_AcquireActorResource(ScriptVm *, u8 *);
extern int ScriptCmd_TurnHandler(ScriptVm *, s32);
extern int ScriptCmd_SetActorResourceFromPaths(ScriptVm *, u8 *);
extern int ScriptCmd_SetActorResourceFromTable(ScriptVm *, u8 *);
extern int FS_UnloadOverlayImage_02026a90(ScriptVm *, u8 *);
extern int ScriptCmd_PostEvent0(ScriptVm *, u8 *);
extern int func_02026ab0(ScriptVm *, s32);
extern int ScriptCmd_RestorePanel(ScriptVm *, u8 *);
extern int ScriptCmd_RestorePanel_02026ad0(ScriptVm *, u8 *);

/* Opcode byte 1 indexes this table; each entry occupies eight bytes. */
ScriptCommandHandler gCoreScriptCommandHandlers[33] = {
    {ScriptCmd_CopyOperandOrInvokeHandler, NULL},
    {ScriptCmd_SetElemOffset, NULL},
    {FSi_CloseFileCommandNoOpA, ByteCode_ExecuteLoadOp},
    {FSi_EmptyArchiveProcThumbStub, NULL},
    {ResetRequestRecord, NULL},
    {ScriptCmd_AdvanceElemCursor, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {ScriptVm_RunCallback, IsDerefZero},
    {FSi_CloseFileCommandNoOpB, FSi_CloseFileCommandNoOpC},
    {ScriptCmd_SetBranchTarget, NULL},
    {ScriptCmd_SetElemFieldFromOperand, ScriptCmd_AdvanceOrSetField},
    {ScriptCmd_ArmPair, NULL},
    {func_02026590, NULL},
    {func_020265ec, NULL},
    {func_02026634, NULL},
    {func_02026678, NULL},
    {func_020266d0, func_02026704},
    {ScriptCmd_QueueSoundKind1, Script_StepAndIsIdle},
    {func_02026754, NULL},
    {func_02026788, NULL},
    {func_020267b8, NULL},
    {func_020267d8, NULL},
    {ScriptCmd_LoadFileToSlot, NULL},
    {ScriptCmd_FreeFileSlot, NULL},
    {ScriptCmd_AcquireActorResource, ScriptCmd_TurnHandler},
    {NULL, NULL},
    {ScriptCmd_SetActorResourceFromPaths, NULL},
    {ScriptCmd_SetActorResourceFromTable, ScriptCmd_TurnHandler},
    {FS_UnloadOverlayImage_02026a90, NULL},
    {ScriptCmd_PostEvent0, func_02026ab0},
    {ScriptCmd_RestorePanel, NULL},
    {ScriptCmd_RestorePanel_02026ad0, NULL}
};

/* Opcode byte 0 selects a group; overlays install the other eight groups. */
ScriptCommandHandler *gScriptHandlerTables[9] = {
    gCoreScriptCommandHandlers, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

/* The low byte is the script busy flag; it starts at -1. */
u32 gScriptState = 0xff;
