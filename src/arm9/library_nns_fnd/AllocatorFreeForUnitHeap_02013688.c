extern void *NNS_FndFreeToUnitHeap();

void *AllocatorFreeForUnitHeap_02013688(void **allocator, void *block) {
    return NNS_FndFreeToUnitHeap(allocator[1], block);
}
