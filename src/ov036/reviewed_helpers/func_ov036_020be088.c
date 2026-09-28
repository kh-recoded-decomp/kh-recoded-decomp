extern int func_02025de4(int a, void *b);
extern void func_020bd4b4(int a, int b);

int func_ov036_020be088(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    func_020bd4b4(a, b);
    return 1;
}
