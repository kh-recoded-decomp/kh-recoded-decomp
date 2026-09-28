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
