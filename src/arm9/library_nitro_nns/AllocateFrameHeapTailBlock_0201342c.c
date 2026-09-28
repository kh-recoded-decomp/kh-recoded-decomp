/* Allocates an aligned block from the frame heap cursor at its high end, optionally clearing new bytes.
 * The paired initializer at ARM9:02013388 sets the FRMH signature and seeds this cursor. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNSi_AllocFromTailOfExpHeap.c.
 * The upstream function label is provenance only, not type evidence; this target is
 * classified from the FRMH initializer and cursor call chain. External calls use
 * target-address bindings. */
extern void func_01ff86fc(unsigned data, void *dst, unsigned size);

void *AllocateFrameHeapTailBlock_0201342c(int *hh, unsigned size, unsigned align) {
    int end = hh[1];
    unsigned new_top = (end - size) & ~(align - 1);
    unsigned bytes;
    if (new_top < (unsigned)hh[0]) return 0;
    bytes = end - new_top;
    if ((unsigned char)hh[-1] & 1) {
        func_01ff86fc(0, (void *)new_top, bytes);
    }
    hh[1] = (int)new_top;
    return (void *)new_top;
}
