/* Passes an output buffer and a helper-selected resource to another helper, then returns the buffer.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_02089908.c. */
extern int func_020ba2a8();
extern void func_0202e09c();

int func_ov027_020ba31c(int arg0, int arg1, int arg2, int arg3, int arg4) {
    func_0202e09c(arg2, arg3, func_020ba2a8(arg0, arg1), arg4);
    return arg2;
}
