/* Starts an operation with a callback and returns whether its result is two; other results are forwarded.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020be8b0.c. */
extern int func_0201193c(void *handler);
extern void func_020737d4(int id);
extern void func_02074174(int req);

int func_ov015_0207414c(void) {
    int r = func_0201193c(&func_02074174);
    if (r != 2) {
        func_020737d4(r);
        return 0;
    }
    return 1;
}
