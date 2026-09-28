extern void *FindListContainHeap(void *heap);
extern void NNS_FndRemoveListObject(void *list, void *heap);

void NNSi_FndFinalizeHeap_02012bb8(void *heap) {
    NNS_FndRemoveListObject(FindListContainHeap(heap), heap);
}
