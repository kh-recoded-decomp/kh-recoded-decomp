/* Invokes a helper on a global handle unless that handle is minus one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_02082b40.c. */
extern void func_0202a638();
extern int data_020b7be0;

void func_ov022_020a7814(void) {
    int v = data_020b7be0;
    if (v == -1) {
        return;
    }
    func_0202a638(v);
}
