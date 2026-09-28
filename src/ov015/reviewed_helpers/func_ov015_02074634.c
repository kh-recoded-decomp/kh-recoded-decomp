/* Selects state three, starts an operation with a callback, and reports success only for result two.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020be850.c. */

extern void func_020737c4(int mode);
extern int func_02011c78(void *cb);
extern void func_020737d4(int result);
extern void func_02074664(void);

int func_ov015_02074634(void) {
    int r;

    func_020737c4(3);
    r = func_02011c78(&func_02074664);
    if (r == 2) {
        return 1;
    }
    func_020737d4(r);
    return 0;
}
