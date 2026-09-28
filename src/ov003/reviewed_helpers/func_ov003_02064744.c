/* Tests bit three in a halfword at offset two of a globally referenced record.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov012/calls/func_ov012_0205b920.c. */
extern int data_020658c0;

int func_ov003_02064744(void) {
    return (*(unsigned short *)(data_020658c0 + 2) & 8) != 0;
}
