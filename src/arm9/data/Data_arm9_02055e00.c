#include "nitro/types.h"

#pragma explicit_zero_data on

extern void FS_UnloadOverlayImage_02026a7c(void);
extern void FSi_CloseFileCommand_020263bc(void);
extern void FSi_CloseFileCommand_020264d0(void);
extern void FSi_CloseFileCommand_020264d4(void);
extern void FSi_EmptyArchiveProc_0202642c(void);
extern void IsDerefZero_020264c0(void);
extern void ResetRequestRecord_02026430(void);
extern void ScriptCmd_AcquireActorResource_02026854(void);
extern void ScriptCmd_AdvanceElemCursor_0202644c(void);
extern void ScriptCmd_ArmPair_02026554(void);
extern void ScriptCmd_CopyOperandOrInvokeHandler_020262cc(void);
extern void ScriptCmd_FreeFileSlot_0202682c(void);
extern void ScriptCmd_LoadFileToSlot_020267fc(void);
extern void ScriptCmd_PostEvent0_02026a88(void);
extern void ScriptCmd_QueueSoundKind1_02026714(void);
extern void ScriptCmd_RestorePanel_02026ab0(void);
extern void ScriptCmd_RestorePanel_02026abc(void);
extern void ScriptCmd_SetActorResourceFromPaths_0202697c(void);
extern void ScriptCmd_SetActorResourceFromTable_02026a3c(void);
extern void ScriptCmd_SetElemFieldFromOperand_0202651c(void);
extern void ScriptCmd_SetElemOffset_02026320(void);
extern void ScriptVm_RunCallback_02026480(void);
extern void Script_StepAndIsIdle_02026728(void);
extern void func_020263c0(void);
extern void func_020264d8(void);
extern void func_02026530(void);
extern void func_0202657c(void);
extern void func_020265d8(void);
extern void func_02026620(void);
extern void func_02026664(void);
extern void func_020266bc(void);
extern void func_020266f0(void);
extern void func_02026740(void);
extern void func_02026774(void);
extern void func_020267a4(void);
extern void func_020267c4(void);
extern void func_020268f8(void);
extern void func_02026a9c(void);
extern void *data_02055e28[];

void *data_02055e28[66] = {
    (void *)ScriptCmd_CopyOperandOrInvokeHandler_020262cc,
    NULL,
    (void *)ScriptCmd_SetElemOffset_02026320,
    NULL,
    (void *)FSi_CloseFileCommand_020263bc,
    (void *)func_020263c0,
    (void *)FSi_EmptyArchiveProc_0202642c,
    NULL,
    (void *)ResetRequestRecord_02026430,
    NULL,
    (void *)ScriptCmd_AdvanceElemCursor_0202644c,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)ScriptVm_RunCallback_02026480,
    (void *)IsDerefZero_020264c0,
    (void *)FSi_CloseFileCommand_020264d0,
    (void *)FSi_CloseFileCommand_020264d4,
    (void *)func_020264d8,
    NULL,
    (void *)ScriptCmd_SetElemFieldFromOperand_0202651c,
    (void *)func_02026530,
    (void *)ScriptCmd_ArmPair_02026554,
    NULL,
    (void *)func_0202657c,
    NULL,
    (void *)func_020265d8,
    NULL,
    (void *)func_02026620,
    NULL,
    (void *)func_02026664,
    NULL,
    (void *)func_020266bc,
    (void *)func_020266f0,
    (void *)ScriptCmd_QueueSoundKind1_02026714,
    (void *)Script_StepAndIsIdle_02026728,
    (void *)func_02026740,
    NULL,
    (void *)func_02026774,
    NULL,
    (void *)func_020267a4,
    NULL,
    (void *)func_020267c4,
    NULL,
    (void *)ScriptCmd_LoadFileToSlot_020267fc,
    NULL,
    (void *)ScriptCmd_FreeFileSlot_0202682c,
    NULL,
    (void *)ScriptCmd_AcquireActorResource_02026854,
    (void *)func_020268f8,
    NULL,
    NULL,
    (void *)ScriptCmd_SetActorResourceFromPaths_0202697c,
    NULL,
    (void *)ScriptCmd_SetActorResourceFromTable_02026a3c,
    (void *)func_020268f8,
    (void *)FS_UnloadOverlayImage_02026a7c,
    NULL,
    (void *)ScriptCmd_PostEvent0_02026a88,
    (void *)func_02026a9c,
    (void *)ScriptCmd_RestorePanel_02026ab0,
    NULL,
    (void *)ScriptCmd_RestorePanel_02026abc,
    NULL,
};

void *data_02055e04[9] = {
    (void *)data_02055e28,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u32 data_02055e00[1] = {
    0x000000FF,
};
