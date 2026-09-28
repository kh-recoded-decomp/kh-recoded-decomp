/* Visits an array of 0x58-byte records twice, applying one helper during each pass.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_0208417c.c. */

extern void func_020b8cbc(int ctx, int element);
extern void func_020b85d0(int ctx, int element);
void func_ov027_020b8f5c(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        func_020b8cbc(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        func_020b85d0(ctx, base + i * 0x58);
    }
}
