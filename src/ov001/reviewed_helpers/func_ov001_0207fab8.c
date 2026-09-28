extern int func_02025de4(int a, void *b);
extern void func_0207eeb4(int a, int b, int c);

int func_ov001_0207fab8(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    int c = func_02025de4(param_1, param_2 + 8);
    func_0207eeb4(a, b, c);
    return 1;
}
