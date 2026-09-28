/* Walks variable-size records, allocates and copies each payload after its eight-byte header, and passes its kind to a helper.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_02082bbc.c. */

extern void *func_0202a19c(int size, int align);
extern void func_01ff878c(const void *src, void *dst, int size);
extern void func_020b80f0(int owner, void *obj, unsigned short kind);
void func_ov027_020b7780(int param_1, int param_2) {
    unsigned int n = *(unsigned int *)param_2;
    unsigned int i;
    int p = param_2 + 4;
    for (i = 0; i < n; i++) {
        void *obj = func_0202a19c(*(int *)p - 8, 4);
        func_01ff878c((const void *)(p + 8), obj, *(int *)p - 8);
        func_020b80f0(param_1, obj, *(unsigned short *)(p + 4));
        p += *(int *)p;
    }
}
