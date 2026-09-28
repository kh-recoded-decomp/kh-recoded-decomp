/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void *func_02014e00();
extern void func_02014d74();

int func_02014d38(int this_, int *arg1) {
    void *r = func_02014e00(this_, 0x43484152);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    func_02014d74((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
