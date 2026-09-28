/* Runs two helpers in sequence, forwarding all four arguments to the first and arguments one, two, and four to the second.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_0208359c.c. */

extern void func_020b81d8(int a, int b, int c, int d);
extern void func_020b81e0(int a, int b, int d);
void func_ov027_020b81e8(int param_1, int param_2, int param_3, int param_4) {
    func_020b81d8(param_1, param_2, param_3, param_4);
    func_020b81e0(param_1, param_2, param_4);
}
