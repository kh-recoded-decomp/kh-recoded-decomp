/* Temporarily applies two supplied halfwords, runs a helper, and reapplies the original signed halfwords.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_02089560.c. */
extern void func_020b81e8();
extern void func_020b8210();

void func_ov027_020b822c(int arg0, int arg1, unsigned short arg2, unsigned short arg3) {
    short v1 = *(short *)(arg1 + 2);
    short v2 = *(short *)(arg1 + 4);
    func_020b81e8(arg0, arg1, arg2, arg3);
    func_020b8210(arg0, arg1);
    func_020b81e8(arg0, arg1, v1, v2);
}
