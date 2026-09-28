/* Dispatches an error or continuation result, then selects state nine when the continuation finishes.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020bef74.c. */
extern void func_020737d4(unsigned int id);
extern void func_02074ec8(void);
extern int func_02074698(void);
extern void func_020737c4(int state);


void func_ov015_02074664(int req) {
    if (*(unsigned short *)(req + 2) != 0) {
        func_020737d4(*(unsigned short *)(req + 2));
        func_02074ec8();
        return;
    }
    if (func_02074698() != 0) {
        return;
    }
    func_020737c4(9);
}
