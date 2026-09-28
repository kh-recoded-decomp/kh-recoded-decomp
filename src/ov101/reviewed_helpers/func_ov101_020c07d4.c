/* Passes an indexed eight-byte table entry payload and a second argument to a lookup helper.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/calls/func_0202c208.c. */

extern void *func_0202d44c();
extern int data_020c4d20;

void *func_ov101_020c07d4(int index, int arg2) {
    return func_0202d44c(data_020c4d20 + 4 + index * 8, arg2);
}
