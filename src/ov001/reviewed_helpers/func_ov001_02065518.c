extern int func_02025de4(int vm, unsigned short *pc);
extern void func_02067ee4(int a, int b, unsigned int flag);

int func_ov001_02065518(int vm, unsigned short *pc) {
    int a = func_02025de4(vm, pc);
    int b = func_02025de4(vm, pc + 4);
    int c = func_02025de4(vm, pc + 8);
    func_02067ee4(a, b, (unsigned int)(c != 0));
    return 1;
}
