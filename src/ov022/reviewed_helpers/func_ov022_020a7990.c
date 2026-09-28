/* Returns true for an inactive state; otherwise requires a nonzero threshold reached by a helper-reported position.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02083414.c. */

extern int func_020a73d8(void);
extern int func_020a8918(void);

int func_ov022_020a7990(int unused, int frames) {
    int buffered;

    if (func_020a73d8() == 0) {
        return 1;
    }
    if (frames == 0) {
        return 0;
    }

    buffered = func_020a8918();
    if (buffered < frames) {
        return 0;
    }
    if (buffered >= frames) {
        return 1;
    }
    return 1;
}
