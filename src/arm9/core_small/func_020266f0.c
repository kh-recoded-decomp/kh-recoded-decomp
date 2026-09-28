/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_0204da48(void);
extern void func_0204d73c(unsigned a);
extern unsigned char data_02055e00;

int func_020266f0(int param_1, int param_2) {
    if (func_0204da48() == 0) {
        data_02055e00 = param_2;
        func_0204d73c(param_2 & 0xff);
        return 1;
    }
    return 0;
}
