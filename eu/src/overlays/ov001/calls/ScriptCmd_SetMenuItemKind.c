extern int ScriptVm_ReadOperandInt(int vm, unsigned short *pc);
extern void SetMenuItemKind(int a, int b, unsigned int flag);

int ScriptCmd_SetMenuItemKind(int vm, unsigned short *pc) {
    int a = ScriptVm_ReadOperandInt(vm, pc);
    int b = ScriptVm_ReadOperandInt(vm, pc + 4);
    int c = ScriptVm_ReadOperandInt(vm, pc + 8);
    SetMenuItemKind(a, b, (unsigned int)(c != 0));
    return 1;
}
