/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_02025de4(void *a);
extern int func_0204da48(int x);
extern void func_02025e18(void *a, int b);
extern void func_0204d73c(int x);
extern unsigned char data_02055e00;

int func_020266bc(void *obj, int arg1) {
    int r4 = func_02025de4(obj);
    if (func_0204da48(r4) != 0) {
        func_02025e18(obj, r4);
        return 0;
    }
    data_02055e00 = r4;
    func_0204d73c(r4 & 0xff);
    return 1;
}
