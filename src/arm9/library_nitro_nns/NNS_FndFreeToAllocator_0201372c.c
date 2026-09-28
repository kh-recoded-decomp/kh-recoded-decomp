typedef void (*FreeFn)(void *allocator, void *block);

void NNS_FndFreeToAllocator_0201372c(void *allocator, void *block) {
    FreeFn *vt = *(FreeFn **)allocator;
    vt[1](allocator, block);
}
