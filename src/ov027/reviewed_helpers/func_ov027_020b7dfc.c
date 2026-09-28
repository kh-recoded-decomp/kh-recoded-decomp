extern void func_020b831c(int);
extern void func_0202a1c4(void *);
void func_ov027_020b7dfc(int param_1) {
    void *p;
    func_020b831c(param_1);
    p = *(void **)(param_1 + 0x14); if (p != 0) func_0202a1c4(p);
    p = *(void **)(param_1 + 0x10); if (p != 0) func_0202a1c4(p);
    p = *(void **)(param_1 + 0xc); if (p != 0) func_0202a1c4(p);
}
