/* When a result halfword equals eight, selects state nine and invokes the terminating helper.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov105/calls/func_ov105_020bf64c.c. */

extern void func_020737c4(int);
extern void func_02004cf0(void);
void func_ov015_02074ce0(char *scene) {
    if (*(unsigned short *)(scene + 2) == 8) {
        func_020737c4(9);
        func_02004cf0();
    }
}
