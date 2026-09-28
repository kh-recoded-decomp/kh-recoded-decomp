/* Rounds request to words and chooses the frame heap low/high cursor by signed alignment.
 * The wrapper addresses cursors initialized by ARM9:02013388. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndAllocFromExpHeapEx_0x02010bcc.c.
 * The upstream function label is provenance only, not type evidence; this target is
 * classified from the FRMH initializer and cursor call chain. External calls use
 * target-address bindings. */
extern void *AllocateFrameHeapTailBlock_0201342c(void *hh, unsigned size, unsigned align);
extern void *AllocateFrameHeapHeadBlock_020133d0(void *hh, unsigned size, unsigned align);

void *AllocateFromFrameHeap_02013508(void *heap, unsigned size, int align) {
    if (size == 0) size = 1;
    size = (size + 3) & ~3;
    heap = (char *)heap + 0x24;
    if (align >= 0) {
        return AllocateFrameHeapHeadBlock_020133d0(heap, size, (unsigned)align);
    } else {
        return AllocateFrameHeapTailBlock_0201342c(heap, size, (unsigned)-align);
    }
}
