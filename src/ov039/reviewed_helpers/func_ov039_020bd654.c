/* Reads the word at offset sixteen from the object selected by a global eight-byte table index.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/auto/func_ov025_02085890.c. */
extern int data_020bea84;
extern int data_020be930;

int func_ov039_020bd654(void) {
    return *(int *)(*(int *)((char *)&data_020be930 + *(int *)&data_020bea84 * 8) + 0x10);
}
