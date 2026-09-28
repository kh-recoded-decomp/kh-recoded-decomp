extern void *NNS_FndAllocFromFrmHeapEx();

void *AllocatorAllocForFrmHeap_02013698(void **allocator, unsigned int size) {
    return NNS_FndAllocFromFrmHeapEx(allocator[1], size, allocator[2]);
}
