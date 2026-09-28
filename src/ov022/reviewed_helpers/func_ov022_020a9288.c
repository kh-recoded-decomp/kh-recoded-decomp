/* When a context is nonnull, passes it to two cleanup helpers in sequence.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02084fac.c. */

extern void func_020a941c(int *ctx);
extern void func_020a93e0(int *p);

void func_ov022_020a9288(int *ctx) {
    if (ctx != 0 && ctx != 0) {
        func_020a941c(ctx);
        func_020a93e0(ctx);
    }
}
