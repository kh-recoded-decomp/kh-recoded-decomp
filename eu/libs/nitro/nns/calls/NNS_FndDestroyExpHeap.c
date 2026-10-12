extern void NNSi_FndFinalizeHeap(void *heap);

void NNS_FndDestroyExpHeap(void *heap)
{
    NNSi_FndFinalizeHeap(heap);
}
