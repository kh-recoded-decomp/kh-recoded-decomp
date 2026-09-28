/* Creates an object from a descriptor and caller argument and stores its returned handle in a global.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_02082b1c.c. */
extern int func_0202a448();
extern int data_020bb304;
extern int data_020bb300;

void func_ov028_020bafc8(int arg0) {
    data_020bb300 = func_0202a448(&data_020bb304, arg0);
}
