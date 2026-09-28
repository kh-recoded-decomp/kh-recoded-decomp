extern int NNSi_FndFreeFromDefaultHeap();

int ZeroHalfThenFree_0202cd78(void *arg0) {
    *(short *)arg0 = 0;
    return NNSi_FndFreeFromDefaultHeap(arg0);
}
