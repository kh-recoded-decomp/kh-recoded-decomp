/* Conditionally invokes a callback at offset 0x40, then clears the destination word at offset 0x14.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/auto/func_ov026_02083304.c. */
struct A {
    char pad[0x40];
    void (*fn)(void *);
};

void func_ov027_020b7f60(struct A *a, void *b, int c) {
    if (c != 0 && a->fn != 0) {
        a->fn(b);
    }
    *(int *)((char *)b + 0x14) = 0;
}
