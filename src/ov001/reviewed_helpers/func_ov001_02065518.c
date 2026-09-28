/* Evaluates three argument records, converts the third result to a boolean, forwards them, and returns one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov002/calls/func_ov002_02074c04.c. */
extern int func_02025de4(int vm, unsigned short *pc);
extern void func_02067ee4(int a, int b, unsigned int flag);

int func_ov001_02065518(int vm, unsigned short *pc) {
    int a = func_02025de4(vm, pc);
    int b = func_02025de4(vm, pc + 4);
    int c = func_02025de4(vm, pc + 8);
    func_02067ee4(a, b, (unsigned int)(c != 0));
    return 1;
}
