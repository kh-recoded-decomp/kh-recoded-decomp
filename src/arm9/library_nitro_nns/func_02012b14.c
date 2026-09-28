/* Returns root heap list or the child list belonging to the containing heap.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/FindListContainHeap.c.
 * Original routine: FindListContainHeap. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Returns the child list that contains `heap`, or the root list when it is top level. */
extern void *FindContainHeap(void *list, void *heap);
extern char data_0205a8b4;

void *FindContainingHeapList_02012b14(void *heap) {
    char *list = &data_0205a8b4;
    void *found = FindContainHeap(list, heap);
    if (found != 0) {
        list = (char *)found + 0xc;
    }
    return list;
}
