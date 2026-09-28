/* Selects a callback through a helper-supplied table index and invokes it when nonnull.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_02083a78.c. */
extern int func_020baaf8();
extern int data_020be79c;

void func_ov039_020bb6e8(void) {
    int (*f)(void) = ((int (**)(void))&data_020be79c)[func_020baaf8()];
    if (f != 0) {
        f();
    }
}
