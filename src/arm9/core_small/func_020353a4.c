extern void func_0202eee8(int);

void func_020353a4(int *param_1) {
    if ((*param_1 & 0x20) == 0) {
        func_0202eee8((int)param_1 + 4);
    }
    *param_1 |= 0x20;
}
