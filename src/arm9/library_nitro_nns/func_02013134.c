/* Rounds request to words and allocates from head or tail according to signed alignment.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/NNS_FndAllocFromExpHeapEx.c.
 * Original routine: NNS_FndAllocFromExpHeapEx. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Rounds the request up to a word and allocates from the head (positive alignment) or the
 * tail (negative alignment) of the expanded heap. */
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
