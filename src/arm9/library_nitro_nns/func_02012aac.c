/* Recursively finds the deepest heap range containing a given address.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/FindContainHeap.c.
 * Original routine: FindContainHeap. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Depth-first search for the innermost heap whose [start,end) range contains `p`.
 *
 * The recursive result is RETURNED when it is non-null (the ROM's `moveq r0,r4` is
 * followed by an unconditional pop, not a `popeq`), so the child heap wins over its
 * parent; written as `if (child == 0) return heap;` mwcc predicates the return instead. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *FindContainingHeap_02012aac(void *list, char *p) {
    char *heap = NNS_FndGetNextListObject(list, 0);
    while (heap != 0) {
        if (*(char **)(heap + 0x18) <= p && p < *(char **)(heap + 0x1c)) {
            char *inner = FindContainingHeap_02012aac(heap + 0xc, p);
            if (inner == 0) {
                inner = heap;
            }
            return inner;
        }
        heap = NNS_FndGetNextListObject(list, heap);
    }
    return 0;
}
