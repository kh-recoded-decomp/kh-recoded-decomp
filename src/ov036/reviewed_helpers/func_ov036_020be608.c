/* Evaluates two argument records eight bytes apart, forwards both results to a helper, and returns one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/calls/func_02022460.c. */
extern int func_02025de4(int a, void *b);
extern void func_020bd414(int a, int b);

int func_ov036_020be608(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    func_020bd414(a, b);
    return 1;
}
