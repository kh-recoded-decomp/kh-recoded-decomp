/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_02025de4(int a, void *b);
extern void func_0204d960(int a, int b, int c);

int func_02026774(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    int c = func_02025de4(param_1, param_2 + 8);
    func_0204d960(a, b, c);
    return 1;
}
