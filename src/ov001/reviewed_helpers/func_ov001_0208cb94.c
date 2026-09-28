/* Evaluates and resolves an argument, forwards its low sixteen bits with two zeros, and returns one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov023/calls/func_ov023_02084620.c. */
extern int func_02025de4(int vm, unsigned short *pc);
extern unsigned int func_02025960(int vm, int idx);
extern void func_02036198(unsigned int a, int b, int c);

int func_ov001_0208cb94(int vm, unsigned short *pc) {
    int idx = func_02025de4(vm, pc);
    unsigned int resolved = func_02025960(vm, idx);
    func_02036198(resolved & 0xffff, 0, 0);
    return 1;
}
