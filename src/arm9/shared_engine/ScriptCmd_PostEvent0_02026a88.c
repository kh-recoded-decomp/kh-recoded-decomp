extern int ScriptVm_ReadOperandInt_02025de4(void *arg, void *cmd);
extern int func_0204ddc4(int index, int value);

int ScriptCmd_PostEvent0_02026a88(void *arg, void *cmd)
{
    int value = ScriptVm_ReadOperandInt_02025de4(arg, cmd);
    func_0204ddc4(0, value);
    return 0;
}
