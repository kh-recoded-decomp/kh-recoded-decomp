/* Allocates an aligned block from the frame heap cursor at its low end, optionally clearing new bytes.
 * The paired initializer at ARM9:02013388 sets the FRMH signature and seeds this cursor. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNSi_AllocFromHeadOfExpHeap.c.
 * The upstream function label is provenance only, not type evidence; this target is
 * classified from the FRMH initializer and cursor call chain. External calls use
 * target-address bindings. */
extern void func_01ff86fc(unsigned data, void *dst, unsigned size);

void *AllocateFrameHeapHeadBlock_020133d0(int *hh, unsigned size, unsigned align) {
    int start = hh[0];
    int aligned = (int)(((unsigned)((align - 1) + start)) & ~(align - 1));
    int new_top = (int)size + aligned;
    unsigned bytes;
    unsigned char flag;
    if ((unsigned)new_top > (unsigned)hh[1]) return 0;
    flag = (unsigned char)hh[-1];
    bytes = (unsigned)(new_top - start);
    if (flag & 1) {
        func_01ff86fc(0, (void *)start, bytes);
    }
    hh[0] = new_top;
    return (void *)aligned;
}
