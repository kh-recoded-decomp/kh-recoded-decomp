/* Returns false for a null argument; otherwise returns whether a helper result equals one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02085014.c. */

extern int func_020a9cb0(int arg);
int func_ov022_020a9314(int param_1) {
    if (param_1 == 0) return 0;
    return func_020a9cb0(param_1) == 1;
}
