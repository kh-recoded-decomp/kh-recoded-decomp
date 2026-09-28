typedef void *(*AllocFn)(void *allocator, unsigned int size);

void *NNS_FndAllocFromAllocator_02013718(void *allocator, unsigned int size) {
    AllocFn *vt = *(AllocFn **)allocator;
    return vt[0](allocator, size);
}
