/* Clears a record word at offset twelve, releases its nonnull pointer at offset four, and clears that pointer.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_020834d8.c. */
extern int func_0202a1c4();

struct S {
    int unk0;
    int unk4;
    int unk8;
    int unkc;
};

void func_ov027_020b8134(int a0, struct S *a1) {
    a1->unkc = 0;
    if (a1->unk4 != 0) {
        func_0202a1c4(a1->unk4);
        a1->unk4 = 0;
    }
}
