extern int func_02025de4(int a, void *b);
extern void func_020bce5c(int a, int b);

int func_ov036_020bdd30(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    func_020bce5c(a, b);
    return 1;
}
