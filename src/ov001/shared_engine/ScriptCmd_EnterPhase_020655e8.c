extern int ScriptVm_ReadOperandInt();
extern int Ov002_EnterPhase();

int ScriptCmd_EnterPhase_020655e8(int arg0, void *cmd) {
        Ov002_EnterPhase(ScriptVm_ReadOperandInt(arg0, cmd));
    return 1;
}
