extern int ScriptVm_ReadOperandInt(int vm, unsigned short *pc);
extern void func_ov001_02067ee4(int a, int b, unsigned int flag);

int func_ov001_02065518(int vm, unsigned short *pc) {
    int a = ScriptVm_ReadOperandInt(vm, pc);
    int b = ScriptVm_ReadOperandInt(vm, pc + 4);
    int c = ScriptVm_ReadOperandInt(vm, pc + 8);
    func_ov001_02067ee4(a, b, (unsigned int)(c != 0));
    return 1;
}
