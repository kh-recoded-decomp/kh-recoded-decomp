/* Runs an update helper and, when flag bit zero at offset 0x2c is set, runs a second helper.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_0208320c.c. */

extern void func_020b7aa0(int self);
extern void func_020b7c30(int self);
struct pend { unsigned char b0 : 1; };
void func_ov027_020b7dd4(int param_1) {
    func_020b7aa0(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_020b7c30(param_1);
}
