extern int func_02025de4(int vm, unsigned short *pc);
extern unsigned int func_02025960(int vm, int idx);
extern void func_02036198(unsigned int a, int b, int c);

int func_ov001_0208cb94(int vm, unsigned short *pc) {
    int idx = func_02025de4(vm, pc);
    unsigned int resolved = func_02025960(vm, idx);
    func_02036198(resolved & 0xffff, 0, 0);
    return 1;
}
