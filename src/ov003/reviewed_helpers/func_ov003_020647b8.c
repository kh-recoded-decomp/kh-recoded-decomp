/* Resolves an argument and returns whether an inactive state or the helper-reported position satisfies its nonzero threshold.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_020833dc.c. */

extern int func_02025de4(int owner, void *entry);
extern int func_02025e18(int owner, int handle);
extern int func_02063fe4(int handle);
extern int func_020a8918(void);

int func_ov003_020647b8(int owner, void *entry) {
    int len;
    int pos;

    len = func_02025de4(owner, entry);
    if (func_02063fe4(func_02025e18(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = func_020a8918();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
