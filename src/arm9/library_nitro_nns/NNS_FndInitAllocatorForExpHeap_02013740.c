extern int data_02052eec;

void NNS_FndInitAllocatorForExpHeap_02013740(int *allocator, int a, int b) {
    allocator[0] = (int)&data_02052eec;
    allocator[1] = a;
    allocator[2] = b;
    allocator[3] = 0;
}
