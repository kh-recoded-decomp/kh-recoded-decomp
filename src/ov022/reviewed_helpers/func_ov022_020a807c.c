/* Invokes a helper with the node pointer at offset zero, then increments the node counter at offset 0x40.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_0208435c.c. */

extern void func_020a9314(void *sub);
void func_ov022_020a807c(char *node) {
    func_020a9314(*(void **)node);
    *(int *)(node + 0x40) += 1;
}
