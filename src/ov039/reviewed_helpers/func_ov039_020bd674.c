/* Reads the word at offset twelve from a second object table using a second global index.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/auto/func_ov025_020858b0.c. */
extern int data_020bea84;
extern int data_020be8d0;

int func_ov039_020bd674(void) {
    return *(int *)(*(int *)((char *)&data_020be8d0 + *(int *)((char *)&data_020bea84 + 4) * 8) + 0xc);
}
