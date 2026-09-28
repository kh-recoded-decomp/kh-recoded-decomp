/* Evaluates three argument records eight bytes apart, forwards their results to a helper, and returns one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/calls/func_02022484.c. */
extern int func_02025de4(int a, void *b);
extern void func_0207eeb4(int a, int b, int c);

int func_ov001_0207fab8(int param_1, unsigned short *param_2) {
    int a = func_02025de4(param_1, param_2);
    int b = func_02025de4(param_1, param_2 + 4);
    int c = func_02025de4(param_1, param_2 + 8);
    func_0207eeb4(a, b, c);
    return 1;
}
