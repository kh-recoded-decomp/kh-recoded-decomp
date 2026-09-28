/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

extern void func_0204e964(int *a, int *b, int *c, int d);
void func_0204f178(int *base, int idx, int scale) {
    char *e4;
    if (idx < 0) {
        return;
    }
    e4 = (char *)(base + 1) + idx * 0x8c;
    *(int *)((char *)base + idx * 0x8c + 0xc) = scale * -0x800;
    func_0204e964(base, (int *)e4, base + 1, (int)base + idx * 0x8c);
}
