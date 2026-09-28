extern int ScriptVm_ReadOperandInt(int arg, int);
extern void SoundMgr_PrepareStream(int a, int b);
int CmdPrepareStream_020a79e8(int param_1, int arg1) {
    int r = ScriptVm_ReadOperandInt(param_1, arg1);
    SoundMgr_PrepareStream(0, r);
    return 1;
}
