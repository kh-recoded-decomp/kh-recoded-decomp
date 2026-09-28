extern int ScriptVm_ReadOperandInt();
extern int Ov002_World_SetByte8D68();

int ScriptCmd_SetWorldByte8D68_02065460(int arg0, int arg1) {
    signed char x = ScriptVm_ReadOperandInt(arg0, arg1);
    Ov002_World_SetByte8D68(x);
    return 1;
}
