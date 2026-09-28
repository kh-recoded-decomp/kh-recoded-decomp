extern int func_02025dac(int a, void *b);
extern void func_020bc04c(int a, int b);

int func_ov001_020656a0(int param_1, unsigned short *param_2) {
    int a = func_02025dac(param_1, param_2);
    int b = func_02025dac(param_1, param_2 + 4);
    func_020bc04c(a, b);
    return 1;
}
