extern int func_02025de4(void *a, int b);
extern int func_02025df8(void *a, int b);
extern int func_02085bb0(unsigned short a, int *b);
extern void func_0207ee04(int a, int b);

int func_ov001_02080534(void *arg1, int arg2) {
    int r1 = func_02025de4(arg1, arg2);
    int r2 = func_02025de4(arg1, arg2 + 8);
    int local = func_02025df8(arg1, arg2 + 0x10);
    int r = func_02085bb0((unsigned short)r2, &local);
    func_0207ee04(r1, r);
    return 1;
}
