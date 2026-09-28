extern int ScriptVm_ReadOperandInt(int a, int b);
extern int ScriptVm_ReadOperandFx32(int a, int b);
extern void Ov002_SetLinkModeAndValue(int a, int b);
int ScriptCmd_SetLinkMode_02065c5c(int param_1, int param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandFx32(param_1, param_2 + 8);
    Ov002_SetLinkModeAndValue(a, b);
    return 1;
}
