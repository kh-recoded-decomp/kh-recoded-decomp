/* Reports a nonzero halfword result and runs cleanup, or conditionally runs cleanup after a continuation.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020be880.c. */
extern void func_020737d4(unsigned int id);
extern int func_02073d1c(void);
extern void func_02074e80(void);


void func_ov015_02073cec(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_020737d4(*(unsigned short *)(req + 2));
        func_02074e80();
        return;
    }
    if (func_02073d1c() != 0) {
        return;
    }
    func_02074e80();
}
