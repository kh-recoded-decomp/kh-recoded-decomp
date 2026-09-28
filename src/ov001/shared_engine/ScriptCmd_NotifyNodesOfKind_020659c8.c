extern int ScriptVm_ReadOperandInt();
extern int Ov002_NotifyNodesOfKind();

int ScriptCmd_NotifyNodesOfKind_020659c8(int arg0, int arg1) {
    unsigned short x = ScriptVm_ReadOperandInt(arg0, arg1);
    Ov002_NotifyNodesOfKind(x);
    return 1;
}
