extern void *NNS_FndFreeToUnitHeap();

void *AllocatorFreeForUnitHeap_020136d0(void **allocator, void *block) {
    return NNS_FndFreeToUnitHeap(allocator[1], block);
}
