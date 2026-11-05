extern int ScriptVm_ReadOperandInt(int vm, unsigned short *pc);
extern unsigned int ScriptCmd_ReturnValue(int vm, int idx);
extern void SetWorldObjectProbeSphere(unsigned int a, int b, int c);

int ScriptCmd_DisableResolvedActorProbeSphere(int vm, unsigned short *pc) {
    int idx = ScriptVm_ReadOperandInt(vm, pc);
    unsigned int resolved = ScriptCmd_ReturnValue(vm, idx);
    SetWorldObjectProbeSphere(resolved & 0xffff, 0, 0);
    return 1;
}
