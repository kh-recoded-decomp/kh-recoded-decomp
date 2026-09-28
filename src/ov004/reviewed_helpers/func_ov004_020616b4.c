/* Forwards two parameters and the sub display blend-register address 0x04001050 to a helper.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov011/calls/func_ov011_0205b014.c. */
extern void *func_0200686c();

void *func_ov004_020616b4(int this_, int arg1) {
    return func_0200686c(0x04001050, this_, arg1);
}
