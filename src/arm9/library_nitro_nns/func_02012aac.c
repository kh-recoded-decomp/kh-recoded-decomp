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
