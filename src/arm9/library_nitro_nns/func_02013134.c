extern void *AllocFromHead(void *heap, unsigned int size, int align);
extern void *AllocFromTail(void *heap, unsigned int size, int align);

void *AllocateFromExpandedHeapEx_02013134(void *heap, unsigned int size, int align) {
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3u;
    if (align >= 0) {
        return AllocFromHead(heap, size, align);
    }
    return AllocFromTail(heap, size, -align);
}
