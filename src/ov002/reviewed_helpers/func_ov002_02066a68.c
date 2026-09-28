/* Releases a nonnull global pointer through a helper and clears the global.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov002/calls/func_ov002_020711a4.c. */
extern void func_0202a1c4();
extern int data_0206c46c;

void func_ov002_02066a68(void) {
    int p = *(int *)&data_0206c46c;
    if (p == 0) {
        return;
    }
    func_0202a1c4(p);
    data_0206c46c = 0;
}
