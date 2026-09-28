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
