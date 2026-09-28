extern int ScriptVm_ReadOperandInt(int arg, int);
extern void Ov023_OpenDialog(int arg);
int CmdOpenDialog_02065a00(int param_1, int arg1) {
    Ov023_OpenDialog(ScriptVm_ReadOperandInt(param_1, arg1));
    return 0;
}
