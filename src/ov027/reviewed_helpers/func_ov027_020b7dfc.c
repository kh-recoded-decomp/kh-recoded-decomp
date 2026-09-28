/* Runs a cleanup helper and releases each nonnull pointer at offsets 0x14, 0x10, and 0x0c.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_02083234.c. */

extern void func_020b831c(int);
extern void func_0202a1c4(void *);
void func_ov027_020b7dfc(int param_1) {
    void *p;
    func_020b831c(param_1);
    p = *(void **)(param_1 + 0x14); if (p != 0) func_0202a1c4(p);
    p = *(void **)(param_1 + 0x10); if (p != 0) func_0202a1c4(p);
    p = *(void **)(param_1 + 0xc); if (p != 0) func_0202a1c4(p);
}
