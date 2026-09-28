/* Waits for an asynchronous operation when its pending byte is one, then clears that byte.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02085fc4.c. */

extern void func_0200b1e4(int *file);

void func_ov022_020aa2a0(int cur) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        func_0200b1e4(*(int **)(cur + 0xc));
    }
    *(unsigned char *)(cur + 0x10) = 0;
}
