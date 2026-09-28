extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *cmd);
extern void ScriptCmd_SetElemField_02025e18(void *vm, unsigned int value);

int ScriptCmd_SetElemFieldFromOperand_0202651c(void *vm, void *cmd)
{
    int value = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    ScriptCmd_SetElemField_02025e18(vm, value);
    return 0;
}
