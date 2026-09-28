/* Examines two identifiers at word indices five and six and forwards each identifier other than minus one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_0208444c.c. */
extern int func_0204f2c0();

void func_ov027_020b9620(int a, int *b) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = b[i + 5];
        if (v != -1) {
            func_0204f2c0(a, v);
        }
    }
}
