/* Reports a nonzero halfword result or runs a continuation, then selects state nine when appropriate.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020be5cc.c. */
extern void func_020737d4(unsigned int id);
extern void func_020737c4(int state);
extern int func_02074288(void);

void func_ov015_02074250(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_020737d4(*(unsigned short *)(req + 2));
        func_020737c4(9);
        return;
    }
    if (func_02074288() != 0) {
        return;
    }
    func_020737c4(9);
}
