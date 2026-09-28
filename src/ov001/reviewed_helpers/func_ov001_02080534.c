/* Evaluates two arguments and a local value, invokes a helper using the second value truncated to sixteen bits, and forwards its result.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov020/calls/func_ov020_0207fa40.c. */
extern int func_02025de4(void *a, int b);
extern int func_02025df8(void *a, int b);
extern int func_02085bb0(unsigned short a, int *b);
extern void func_0207ee04(int a, int b);

int func_ov001_02080534(void *arg1, int arg2) {
    int r1 = func_02025de4(arg1, arg2);
    int r2 = func_02025de4(arg1, arg2 + 8);
    int local = func_02025df8(arg1, arg2 + 0x10);
    int r = func_02085bb0((unsigned short)r2, &local);
    func_0207ee04(r1, r);
    return 1;
}
